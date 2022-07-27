#pragma once

#include <Shoegaze2/System/Interface/GUI/IPath.h>

#include <nanovg.h>
#include <vector>

#include <iostream>

namespace Shoegaze2Desktop {
    class Path : public Shoegaze2::IPath {
    private:
        enum Instruction {
            MOVE_TO,
            LINE_TO,
            QUAD_TO,
            QUBIC_TO,
            LINE,
            RECT,
            ROUND_RECT,
            ARC,
            CLOSE
        };

        struct PathInstruction {
            Instruction type;
            //float *args = nullptr;
            float args[4] = {};
            int args_count = 0;

            PathInstruction(const Instruction type, const float *p_args, const int count) {
                this->type = type;
                setArgs(p_args, count);
            }

            PathInstruction(const PathInstruction &path) {
                this->type = path.type;
                setArgs(path.args, path.args_count);
            }

            void setArgs(const float *p_args, int count) {
                //if (args != nullptr)
                //delete [] args;

                //args_count = count;
                //args = new float[count];
                args_count = count;
                for (int i = 0; i < count; i++)
                    args[i] = p_args[i];
            }

            void Scale(float x, float y) {
                for (int i = 0; i < args_count; i += 2) {
                    args[i] *= x;
                    args[i+1] *= y;
                }
            }

            void Translate(float x, float y) {
                switch (type) {
                    case MOVE_TO:
                        args[0] += x;
                        args[1] += y;
                        break;
                    case LINE_TO:
                        args[0] += x;
                        args[1] += y;
                        break;
                    case QUAD_TO:
                        args[0] += x;
                        args[1] += y;
                        args[2] += x;
                        args[3] += y;
                        break;
                    case QUBIC_TO:
                        args[0] += x;
                        args[1] += y;
                        args[2] += x;
                        args[3] += y;
                        break;
                    case LINE:
                        args[0] += x;
                        args[1] += y;
                        args[2] += x;
                        args[3] += y;
                        break;
                    case RECT:
                        args[0] += x;
                        args[1] += y;
                        break;
                    case ROUND_RECT:
                        args[0] += x;
                        args[1] += y;
                        break;
                    case ARC:
                        args[0] += x;
                        args[1] += y;
                        break;
                    case CLOSE:
                        break;
                }
            }

            ~PathInstruction() {
                //std::cout << "PathInstruction::dtor" << std::endl;
                //if (args != nullptr)
                //delete [] args;
            }
        };

        std::vector<PathInstruction> instructions;
        NVGcontext *vg;
    public:
        Path(NVGcontext *vg, int capacityHint = 0) {
            this->vg = vg;
            instructions.reserve(capacityHint);
        }

        Path(const Path &path) : Path(path.vg, (int) path.instructions.size()) {
            for (auto &i: path.instructions) {
                instructions.emplace_back(PathInstruction(i.type, i.args, i.args_count));
            }
        }

        void MoveTo(float x, float y) override {
            float p[] = {x, y};
            instructions.emplace_back(MOVE_TO, p, 2);
        }

        void LineTo(float x, float y) override {
            float p[] = {x, y};
            instructions.emplace_back(LINE_TO, p, 2);
        }

        void QuadTo(float cx, float cy, float x, float y) override {
            float p[] = {cx, cy, x, y};
            instructions.emplace_back(QUAD_TO, p, 4);
        }

        void CubicTo(float cx1, float cy1, float cx2, float cy2, float x, float y) override {
            float p[] = {cx1, cy1, cx2, cy2, x, y};
            instructions.emplace_back(QUBIC_TO, p, 6);
        }

        void AppendLine(float x0, float y0, float x1, float y1) override {
            float p[] = {x0, y0, x1, y1};
            instructions.emplace_back(LINE, p, 4);
        }

        void AppendRect(float x, float y, float w, float h) override {
            float p[] = {x, y, w, h};
            instructions.emplace_back(RECT, p, 4);
        }

        void AppendRoundRect(float x, float y, float w, float h, float r) override {
            float p[] = {x, y, w, h, r};
            instructions.emplace_back(ROUND_RECT, p, 5);
        }

        void AppendArc(float x, float y, float w, float h, float startAngle, float angleExt, int type) override {
            float p[] = {x, y, w, h, startAngle, angleExt, (float) type};
            instructions.emplace_back(ARC, p, 7);
        }

        void Close() override {
            float p[] = {};
            instructions.emplace_back(CLOSE, p, 0);
        }

        void Draw(const Shoegaze2::Brush &brush, float tx, float ty, float sx, float sy) override {
            nvgBeginPath(vg);

            nvgSave(vg);
            brush->SetCurrent();
            nvgTranslate(vg, tx, ty);
            nvgScale(vg, sx, sy);



            float area = 0;
            float oX, oY;
            float pX, pY;

            bool closed = false;

            for (int i = 0; i < instructions.size(); i++) {
                //std::cout << instructions[i].type << std::endl;
                float *a = instructions[i].args;
                switch (instructions[i].type) {
                    case MOVE_TO:
                        closed = false;
                        nvgMoveTo(vg, a[0], a[1]);
                        area = 0;
                        pX = oX = a[0];
                        pY = oY = a[1];
                        break;
                    case LINE_TO:
                        nvgLineTo(vg, a[0], a[1]);
                        area += (a[0] - pX) * (a[1] + pY);
                        pX = a[0];
                        pY = a[1];
                        break;
                    case QUAD_TO:
                        nvgQuadTo(vg, a[0], a[1], a[2], a[3]);
                        //area += (a[0] - pX) * (a[1] + pY);
                        //pX = a[0]; pY = a[1];
                        area += (a[2] - pX) * (a[3] + pY);
                        pX = a[2];
                        pY = a[3];
                        break;
                    case QUBIC_TO:
                        nvgBezierTo(vg, a[0], a[1], a[2], a[3], a[4], a[5]);
                        //area += (a[0] - pX) * (a[1] + pY);
                        //pX = a[0]; pY = a[1];
                        //area += (a[2] - pX) * (a[3] + pY);
                        //pX = a[2]; pY = a[3];
                        area += (a[4] - pX) * (a[5] + pY);
                        pX = a[4];
                        pY = a[5];
                        break;
                    case LINE:
                        nvgMoveTo(vg, a[0], a[1]);
                        nvgLineTo(vg, a[2], a[3]);
                        area += (a[0] - pX) * (a[1] + pY);
                        pX = a[0];
                        pY = a[1];
                        area += (a[2] - pX) * (a[3] + pY);
                        pX = a[2];
                        pY = a[3];
                        break;
                    case RECT:
                        nvgRect(vg, a[0], a[1], a[2], a[3]);
                        break;
                    case ROUND_RECT:
                        // fix this (arcw, arch)
                        nvgRoundedRect(vg, a[0], a[1], a[2], a[3], a[4]);
                        break;
                    case ARC: {
                        int dir = NVG_CW;
                        if (a[5] < 0)
                            dir = NVG_CW;
                        else
                            dir = NVG_CCW;

                        nvgArcWH(vg, a[0], a[1], a[2], a[3], a[4], abs(a[5]), dir);
                        break;
                    }
                    case CLOSE:
                        closed = true;
                        nvgClosePath(vg);
                        area += (oX - pX) * (oY + pY);
                        nvgPathWinding(vg, area > 0 ? NVG_SOLID : NVG_HOLE);
                        area = 0;
                        break;
                }
            }

            if (!closed) {
                //nvgClosePath(vg);
                area += (oX - pX) * (oY + pY);
                nvgPathWinding(vg, area > 0 ? NVG_SOLID : NVG_HOLE);
            }

            Shoegaze2::PaintMode mode = brush->GetPaintMode();
            Shoegaze2::Color c = brush->GetPaint()->GetColor();
            NVGcolor color = nvgRGBAf(c.r, c.g, c.b, c.a);

            // TODO: stroke with stroke color, fill with fill color
            if (mode == Shoegaze2::PaintMode::Fill || mode == Shoegaze2::PaintMode::FillStroke) {
                nvgFillColor(vg, color);
                nvgFill(vg);
            } else {
                nvgStrokeWidth(vg, brush->GetStrokeWidth()/((sx+sy)/2));
                nvgStrokeColor(vg, color);
                nvgStroke(vg);
            }
            nvgRestore(vg);
        }



        std::shared_ptr<Shoegaze2::IPath> Transform(float tx, float ty, float sx, float sy) override {
            auto c = std::make_shared<Path>(*this);
            for (auto &i : c->instructions) {
                i.Scale(sx, sy);
                i.Translate(tx, ty);
            }
            return c;
        }

        std::shared_ptr<Shoegaze2::IPath> Copy() override
        {
            return std::make_shared<Path>(*this);
        }

        void Clear() override {
            instructions.clear();
        }

        ~Path() {
            //std::cout << "Path::dtor" << std::endl;
        }
    };
}