/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkFilterShader_DEFINED
#define SkFilterShader_DEFINED

#include "SkShader.h"

class SkColorFilter;

class SkFilterShader : public SkShader {
public:
    SkFilterShader(SkShader* shader, SkColorFilter* filter);
    virtual ~SkFilterShader();

    size_t contextSize() const SK_OVERRIDE;

    class FilterShaderContext : public SkShader::Context {
    public:
        // Takes ownership of shaderContext and calls its destructor.
        FilterShaderContext(const SkFilterShader&, SkShader::Context*, const ContextRec&);
        virtual ~FilterShaderContext();

        uint32_t getFlags() const SK_OVERRIDE;

        void shadeSpan(int x, int y, SkPMColor[], int count) SK_OVERRIDE;

        void set3DMask(const SkMask* mask) SK_OVERRIDE {
            // forward to our proxy
            fShaderContext->set3DMask(mask);
        }

    private:
        SkShader::Context* fShaderContext;

        typedef SkShader::Context INHERITED;
    };

    SK_TO_STRING_OVERRIDE()
    SK_DECLARE_PUBLIC_FLATTENABLE_DESERIALIZATION_PROCS(SkFilterShader)

protected:
    void flatten(SkWriteBuffer&) const SK_OVERRIDE;
    Context* onCreateContext(const ContextRec&, void* storage) const SK_OVERRIDE;


private:
    SkShader*       fShader;
    SkColorFilter*  fFilter;

    typedef SkShader INHERITED;
};

#endif
