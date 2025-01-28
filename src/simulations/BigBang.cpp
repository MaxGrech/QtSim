#include "BigBang.h"

SIM_DECLARE(BigBang, "Big Bang")

void Sim::prepare()
{
    world_size_min = 100;
    world_size_max = 10000;
    steps_per_frame = 1;
    step_seconds = 0.001;
    particle_count = 20000;
    collision_substeps = 10;
    gravity_cell_near_ratio = 0.01;
    //start_particle_radius = 0.05;
    gravity = 0.03;

    start_world_size = 5000;

    SpaceEngine::prepare();

    

}

void Sim::start()
{
    SpaceEngine::start();

    auto universe_particles = newPlanetFromParticleCount(0, 0, 50, 20, particle_count);

    double explode_speed = 100.0;
    double max_perp_speed_ratio = 1;
    double perp_bias = 1;

    double angle_randomness = ((M_PI * 2) / 360.0) * 45.0;

    for (Particle& p : universe_particles)
    {
        double angle = atan2(p.y, p.x) + random(-angle_randomness, angle_randomness);
        double perp_angle = angle + (M_PI / 2.0);
        double dist_ratio = sqrt(p.x * p.x + p.y * p.y) / 20.0;
        double speed = random(0, explode_speed) * (dist_ratio + 0.1);
        double max_perp_speed = speed;
        double perp_speed = random(-max_perp_speed, max_perp_speed) + (max_perp_speed * perp_bias);
        p.vx = cos(angle) * speed + cos(perp_angle) * perp_speed;
        p.vy = sin(angle) * speed + sin(perp_angle) * perp_speed;
    }

    addParticles(universe_particles);

    /*for (int i = 0; i < particle_count; i++)
    {
        double f = ((double)i) / ((double)particle_count);
        double a = f * M_PI * 2;

        double pos_angle = random(-M_PI, M_PI);
        double pos_radius = sqrt(random(0, 1)) * (world_size / 2);

        Particle n;
        n.x = cos(pos_angle) * pos_radius;
        n.y = sin(pos_angle) * pos_radius;
        n.vx = random(-start_particle_speed, start_particle_speed);
        n.vy = random(-start_particle_speed, start_particle_speed);

        double real_radius = start_particle_radius;// *0.01;// random(start_particle_radius, 10.0 * start_particle_radius);


        // Magnify simulated radius
        n.r = real_radius * particle_magnify;//

        // But use real radius to calculate mass
        n.calculateMass(real_radius, 100);
        //n.mass = 1;

        particles.emplace_back(n);
    }*/

    
}

SIM_END