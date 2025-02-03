#include "CurvedSpace.h"
SIM_DECLARE(CurvedSpace, "Curved Space")


void CurvedSpace::prepare()
{
    //options->slider("Panel Count", &panel_count, 1, 36, 1, [this](int count) 
    //{
    //    auto& panels = setLayout(1);
    //    panels[0]->construct<Instance>(radius_mult * 10);
    //});

    options->realtime_slider("Start Radius Mult", &radius_mult, 0.1, 2.0, 0.1);

    //options->realtime_slider("Start Radius Mult", nullptr, 0.1, 2.0, 0.1, [](Instance &instance, double v) 
    //{
    //    instance.radius = v;
    //});
}

//void CurvedSpace::Options(CurvedSpace::Instance *sim)
//{
//    options->realtime_slider("Start Radius Mult", &radius_mult, 0.1, 2.0, 0.1); // Never add same pointer twice
//    options->realtime_slider("Gravity", &sim->gravity, 0.0, 1.0, 0.1);
//}

void CurvedSpace::start()
{
    auto& panels = setLayout(2, 2);

    panels[0]->construct<Instance>(radius_mult * 10);
    panels[1]->construct<Instance>(radius_mult * 20);
    panels[2]->construct<Instance>(radius_mult * 30);
    panels[3]->construct<Instance>(radius_mult * 40);

    //for (Panel* panel : panels)
    //{
    //    panel->create<Instance>();
    //}
}


/// Simulation Instance Logic

void CurvedSpace::Instance::prepare()
{
    main->options->realtime_slider("Gravity", &gravity, 0.0, 1.0, 0.1);

    particles = allocDelaunayTriangleMesh<Particle>(0, 0, width, height, 20);
}

void CurvedSpace::Instance::destroy()
{
}

void CurvedSpace::Instance::process(DrawingContext* ctx)
{
    //instances[ctx.panel_index].process(ctx);
    //cam.setCamera(main_cam);
    //active_context->main_cam.x += 1.0;
    camera->rotation += (gravity / 180.0 * M_PI);
}

void CurvedSpace::Instance::draw(DrawingContext* ctx)
{
    srand(0);

    for (const auto& n : particles)
    {
        //bool scale_graphics = (i % 2) == 0;
        bool scale_graphics = (rand() % 2) == 0;

        //ctx.scaleGraphics(scale_graphics);
        //ctx.scaleGraphics(custom_scaling ? scale_graphics : true);

        ctx->beginPath();
        ctx->circle(n->x, n->y, radius);
        ctx->fill();
    }
}


void CurvedSpace::Instance::mouseDown(MouseInfo mouse)
{
    gravitateSpace(mouse.world_x, mouse.world_y, 1000000);
}

SIM_END
