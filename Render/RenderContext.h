//
// Created by primal on 24-9-21.
//

#pragma once

#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

namespace Emiri
{
    class RenderContext
    {
    public:
        virtual ~RenderContext() = default;

    private:
        virtual bool Initialize() =0;
        virtual void Shutdown() =0;
    };
}


#endif //RENDERCONTEXT_H