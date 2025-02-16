#ifndef FLUID_H
#define FLUID_H
#include "Simulation.h"

SIM_BEG(Fluid)

struct Particle : public Vec2
{
    double vx = 0;
    double vy = 0;

    Particle(){}
    Particle(double x, double y) : Vec2(x,y) {}
};

struct FluidInstance : public SimulationInstance
{
    double world_w = 250.0;
    double world_h = 250.0;

    vector<Particle*> particles;
    vector<Link<Particle>> links;

    DelaunayTriangulation<Particle> delaunay;
    std::vector<Triangle<Particle>> triangles;

    double timestep = 0.1;
    int particle_count = 100;
    double spring_dist = 20.0;
    double spring_stiffness = 1;
    double spring_damping = 0.01;
    double viscosity_strength = 1;
    double viscosity_spring_dist_ratio = 10.0;
    
    void instanceAttributes(Options* options) override;

    void start() override;
    void destroy() override;
    void processScene() override;
    void draw(Panel* ctx) override;

    void applyLinkViscosity(Particle* a, Particle* b, double r, double strength, double dt);
    void applyViscosityAll(double r, double strength, double dt);

    void spring(Particle* a, Particle* b, double restLength, double k, double damping, double deltaTime);
};

struct Fluid : public Simulation<FluidInstance>
{
    int panel_count = 4;

    void prepare() override;
    //void start();
    void projectAttributes(Options *options) override;
    
};


SIM_END(Fluid)
#endif