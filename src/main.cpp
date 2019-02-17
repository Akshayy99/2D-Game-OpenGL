#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "coin.h"
#include "powerup.h"
#include "magnet.h"
#include "boomerang.h"
#include "laser.h"
#include "fireline.h"
#include "waterballoon.h"
#include "ring.h"
#include "shield.h"
#include "dragon.h"
#include "score.h"
#include "jetfire.h"
#include "semicircle.h"
#include "iceball.h"
#include "hi.h"
#include "wall.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
 
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0.2;
float camera_rotation_angle = 0;
const int NUM_SECONDS = 10;

int score = 0;
int lives = 10;
bool takkar_flag = false;
bool life_flag = false;
bool shield_on = false;
bool jet_pack = false;
bool field_on = false;
bool in_tunnel = false;
int shield_strength = 5;
bool pause = false;
Timer t60(1.0 / 80);


#define PI 3.14159265
#define M 1e7
#define num_coins 300
#define num_powerups 50
#define num_boomerangs 30
#define num_lasers 30
#define num_firelines 100
#define num_waterballoons 100
#define num_rings 100
#define num_jetfires 100
#define num_iceballs 100

int balloons_zinda = 0;
int jetfires_zinda = 0;
int iceballs_zinda = 0;
int level = 1;
float angle = 180.00;
int tym = 0;
Wall wall;
Ball bunny;
Platform platform;
Hi hi;
Score scorr[4];
Score levels[6];
Score live[7];
Coin coins1[num_coins];
Coin coins2[num_coins];
Powerup powerups1[num_powerups];
Powerup powerups2[num_powerups];
Boomerang boomerangs[num_boomerangs];
Laser lasers[num_lasers];
Fireline firelines[num_firelines];
Magnet magnet;
Waterballoon waterballoons[num_waterballoons];
Ring rings[num_rings];
Shield shield;
Dragon viserion;
Jetfire jetfires[num_jetfires];
Semicircle tunnel;
Iceball iceballs[num_iceballs];

bool zinda_balloons[num_waterballoons];
bool zinda_jetfires[num_jetfires];
bool zinda_iceballs[num_iceballs];

int a0, a1, a2, b0, b1, b2, c0, c1, c2, d0, d1, d2, e0, e1, e2, f0, f1, f2, g0, g1, g2;
int a3, b3, c3, d3, e3, f3, g3;
int al, bl, cl, dl, el, fl, gl;
int a4, a5;
int b4, b5;
int c4, c5;
int d4, d5;
int e4, e5;
int f4, f5;
int g4, g5;
int ones, tens, huns, thou;
int onel, tenl;

void draw() {

    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    glUseProgram (programID);
    glm::vec3 eye ( 0, 0, 100);
    glm::vec3 target (0, 0, 0);
    glm::vec3 up (0, 1, 0);

    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Scene render
    platform.draw(VP);
    wall.draw(VP, level);
    if(tym<100)
    {
        hi.draw(VP);
    }
    else{
        bunny.draw(VP, jet_pack);
        tunnel.draw(VP);
        // iceballs[0].draw(VP);
        ones = score % 10;
        tens = (score / 10) % 10;
        huns = (score / 100) % 10;
        thou = (score / 1000) % 10;

        onel = lives % 10;
        tenl = lives/10;

        a0 = (huns==0 || huns==2 || huns==3 || huns==5 || huns==6 || huns==7 || huns==8 || huns==9) ? 1: 0;
        a1 = (tens==0 || tens==2 || tens==3 || tens==5 || tens==6 || tens==7 || tens==8 || tens==9) ? 1: 0;
        a2 = (ones==0 || ones==2 || ones==3 || ones==5 || ones==6 || ones==7 || ones==8 || ones==9) ? 1: 0;

        b0 = (huns==0 || huns==2 || huns==3 || huns==1 || huns==4 || huns==7 || huns==8 || huns==9) ? 1: 0;
        b1 = (tens==0 || tens==2 || tens==3 || tens==1 || tens==4 || tens==7 || tens==8 || tens==9) ? 1: 0;
        b2 = (ones==0 || ones==2 || ones==3 || ones==1 || ones==4 || ones==7 || ones==8 || ones==9) ? 1: 0;

        c0 = (huns==0 || huns==1 || huns==3 || huns==4 || huns==5 || huns==6 || huns==7 || huns == 8 || huns == 9) ? 1: 0;
        c1 = (tens==0 || tens==1 || tens==3 || tens==4 || tens==5 || tens==6 || tens==7 || tens == 8 || tens == 9) ? 1: 0;
        c2 = (ones==0 || ones==1 || ones==3 || ones==4 || ones==5 || ones==6 || ones==7 || ones == 8 || ones == 9) ? 1: 0;

        d0 = (huns==0 || huns==2 || huns==3 || huns==5 || huns==6 || huns==8 || huns==9) ? 1: 0;
        d1 = (tens==0 || tens==2 || tens==3 || tens==5 || tens==6 || tens==8 || tens==9) ? 1: 0;
        d2 = (ones==0 || ones==2 || ones==3 || ones==5 || ones==6 || ones==8 || ones==9) ? 1: 0;

        e0 = (huns==0 || huns==2 || huns==6 || huns==8) ? 1 : 0;
        e1 = (tens==0 || tens==2 || tens==6 || tens==8) ? 1 : 0;
        e2 = (ones==0 || ones==2 || ones==6 || ones==8) ? 1 : 0;

        f0 = (huns==0 || huns==4 || huns==5 || huns==6 || huns==8 || huns==9) ? 1 : 0;
        f1 = (tens==0 || tens==4 || tens==5 || tens==6 || tens==8 || tens==9) ? 1 : 0;
        f2 = (ones==0 || ones==4 || ones==5 || ones==6 || ones==8 || ones==9) ? 1 : 0;

        g0 = (huns==2 || huns==3 || huns==4 || huns==5 || huns==6 || huns==8 || huns==9) ? 1 : 0;
        g1 = (tens==2 || tens==3 || tens==4 || tens==5 || tens==6 || tens==8 || tens==9) ? 1 : 0;
        g2 = (ones==2 || ones==3 || ones==4 || ones==5 || ones==6 || ones==8 || ones==9) ? 1 : 0;

        a3 = (thou==0 || thou==2 || thou==3 || thou==5 || thou==6 || thou==7 || thou==8 || thou==9) ? 1: 0;
        b3 = (thou==0 || thou==2 || thou==3 || thou==1 || thou==4 || thou==7 || thou==8 || thou==9) ? 1: 0;
        c3 = (thou==0 || thou==1 || thou==3 || thou==4 || thou==5 || thou==6 || thou==7 || thou == 8 || huns == 9) ? 1: 0;
        d3 = (thou==0 || thou==2 || thou==3 || thou==5 || thou==6 || thou==8 || thou==9) ? 1: 0;
        e3 = (thou==0 || thou==2 || thou==6 || thou==8) ? 1 : 0;
        f3 = (thou==0 || thou==4 || thou==5 || thou==6 || thou==8 || thou==9) ? 1 : 0;
        g3 = (thou==2 || thou==3 || thou==4 || thou==5 || thou==6 || thou==8 || thou==9) ? 1 : 0;

        scorr[0].draw(VP, a0, b0, c0, d0, e0, f0, g0, 0);
        scorr[1].draw(VP, a1, b1, c1, d1, e1, f1, g1, 0);
        scorr[2].draw(VP, a2, b2, c2, d2, e2, f2, g2, 0);
        scorr[3].draw(VP, a3, b3, c3, d3, e3, f3, g3, 0);

        al = (level==0 || level==2 || level==3 || level==5 || level==6 || level==7 || level==8 || level==9) ? 1: 0;
        bl = (level==0 || level==2 || level==3 || level==1 || level==4 || level==7 || level==8 || level==9) ? 1: 0;
        cl = (level==0 || level==1 || level==3 || level==4 || level==5 || level==6 || level==7 || level == 8 || huns == 9) ? 1: 0;
        dl = (level==0 || level==2 || level==3 || level==5 || level==6 || level==8 || level==9) ? 1: 0;
        el = (level==0 || level==2 || level==6 || level==8) ? 1 : 0;
        fl = (level==0 || level==4 || level==5 || level==6 || level==8 || level==9) ? 1 : 0;
        gl = (level==2 || level==3 || level==4 || level==5 || level==6 || level==8 || level==9) ? 1 : 0;

        levels[0].draw(VP, 0, 0, 0, 1, 1, 1, 0, 0);
        levels[1].draw(VP, 1, 0, 0, 1, 1, 1, 1, 0);
        levels[2].draw(VP, 0, 0, 0, 0, 0, 0, 0, 1);
        levels[3].draw(VP, 1, 0, 0, 1, 1, 1, 1, 0);
        levels[4].draw(VP, 0, 0, 0, 1, 1, 1, 0, 0);

        levels[5].draw(VP, al, bl, cl, dl, el, fl, gl, 0);

        a4 = (tenl==0 || tenl==2 || tenl==3 || tenl==5 || tenl==6 || tenl==7 || tenl==8 || tenl==9) ? 1: 0;
        a5 = (onel==0 || onel==2 || onel==3 || onel==5 || onel==6 || onel==7 || onel==8 || onel==9) ? 1: 0;

        b4 = (tenl==0 || tenl==2 || tenl==3 || tenl==1 || tenl==4 || tenl==7 || tenl==8 || tenl==9) ? 1: 0;
        b5 = (onel==0 || onel==2 || onel==3 || onel==1 || onel==4 || onel==7 || onel==8 || onel==9) ? 1: 0;

        c4 = (tenl==0 || tenl==1 || tenl==3 || tenl==4 || tenl==5 || tenl==6 || tenl==7 || tenl == 8 || tenl == 9) ? 1: 0;
        c5 = (onel==0 || onel==1 || onel==3 || onel==4 || onel==5 || onel==6 || onel==7 || onel == 8 || onel == 9) ? 1: 0;

        d4 = (tenl==0 || tenl==2 || tenl==3 || tenl==5 || tenl==6 || tenl==8 || tenl==9) ? 1: 0;
        d5 = (onel==0 || onel==2 || onel==3 || onel==5 || onel==6 || onel==8 || onel==9) ? 1: 0;

        e4 = (tenl==0 || tenl==2 || tenl==6 || tenl==8) ? 1 : 0;
        e5 = (onel==0 || onel==2 || onel==6 || onel==8) ? 1 : 0;

        f4 = (tenl==0 || tenl==4 || tenl==5 || tenl==6 || tenl==8 || tenl==9) ? 1 : 0;
        f5 = (onel==0 || onel==4 || onel==5 || onel==6 || onel==8 || onel==9) ? 1 : 0;

        g4 = (tenl==2 || tenl==3 || tenl==4 || tenl==5 || tenl==6 || tenl==8 || tenl==9) ? 1 : 0;
        g5 = (onel==2 || onel==3 || onel==4 || onel==5 || onel==6 || onel==8 || onel==9) ? 1 : 0;


        live[0].draw(VP, 0, 0, 0, 1, 1, 1, 0, 0);
        live[1].draw(VP, 0, 1, 1, 0, 0, 0, 0, 0);
        live[2].draw(VP, 0, 0, 0, 0, 0, 0, 0, 1);
        live[3].draw(VP, 1, 0, 0, 1, 1, 1, 1, 0);
        live[4].draw(VP, 1, 0, 1, 1, 0, 1, 1, 0);
        live[5].draw(VP, a4, b4, c4, d4, e4, f4, g4, 0);
        live[6].draw(VP, a5, b5, c5, d5, e5, f5, g5, 0);

        magnet.draw(VP);
        if(shield_on) shield.draw(VP, level);
        viserion.draw(VP);
        // if(balloons_zinda) waterballoons[1].draw(VP);
        for(int i=0;i<num_waterballoons;i++)
        {
            if(zinda_balloons[i] && !waterballoons[i].hit) {
                waterballoons[i].draw(VP);
            }
        }
        // if(jet_pack){
        for(int i=0;i<num_jetfires;i++)
        {
            if(zinda_jetfires[i] ) {
                jetfires[i].draw(VP);
                // cout << "jetfire " << i << " is drawn" << endl;
            }
        }
        for(int i=0;i<num_iceballs;i++)
        {
            // cout << "lol" << endl;
            if(zinda_iceballs[i] && !iceballs[i].hit) iceballs[i].draw(VP);
        }
        // }
        for(int i=0; i<num_coins; i++)
        {
            if(!coins1[i].scored)
                coins1[i].draw(VP);
            if(!coins2[i].scored)
                coins2[i].draw(VP);
        }
        for(int i=0;i<num_powerups;i++)
        {
            if(!powerups1[i].scored && !powerups1[i].far)  
                powerups1[i].draw(VP);
            if(!powerups2[i].scored && !powerups2[i].far)  
                powerups2[i].draw(VP);
        }
        for(int i=0;i<num_boomerangs;i++)
        {
            if(!boomerangs[i].injure)
                boomerangs[i].draw(VP, level);
        }
        for(int i=0;i<num_lasers;i++)
        {
            if(!lasers[i].injure && !lasers[i].balloon_hit)
                lasers[i].draw(VP);
        }
        for(int i=0;i<num_firelines;i++)
        {
            if(!firelines[i].injure && !firelines[i].balloon_hit)
                firelines[i].draw(VP);
        }
        for(int i=0;i<num_rings;i++)
        {
            if(!rings[i].scored)
                rings[i].draw(VP);
        }
    }
    // if(shield_on) shield.draw(VP);
    // shield.draw(VP);

}

bounding_box_t bunny_ka_dabba;
bounding_box_t coins1_ka_dabba[num_coins];
bounding_box_t coins2_ka_dabba[num_coins];
bounding_box_t powerups1_ka_dabba[num_coins];
bounding_box_t powerups2_ka_dabba[num_coins];
bounding_box_t boomerangs_ka_dabba[num_boomerangs];
bounding_box_t lasers1_ka_dabba[num_lasers];
bounding_box_t lasers2_ka_dabba[num_lasers];
bounding_box_t lasers3_ka_dabba[num_lasers];
bounding_box_t lasers4_ka_dabba[num_lasers];
bounding_box_t firelines_ka_dabba1[num_firelines];
bounding_box_t firelines_ka_dabba2[num_firelines];
bounding_box_t waterballoons_ka_dabba[num_waterballoons];
bounding_box_t rings_ka_dabba[num_rings];
bounding_box_t shield_ka_dabba;
bounding_box_t tunnel_ka_dabba;
bounding_box_t iceballs_ka_dabba[num_iceballs];

void tick_elements(float player_x, float player_y) {
    tym++;
    bunny.tick();
    if(bunny.position.x > 30)
    {
        level = 2;
    }
    if(bunny.position.x - screen_center_x > 0)
    {
        screen_center_x += bunny.speed;
        reset_screen();
    }
    if(bunny.position.x - screen_center_x < -2.5)
    {
        screen_center_x -= bunny.speed;
        reset_screen();
    }
    viserion.tick(bunny.position.x, bunny.position.y);
    float r = tunnel.radius1 + tunnel.radius2/2 - 1.1;
    float x = tunnel.position.x, y = tunnel.position.y;
    // cout << "ABC" << bunny.position.x << " " << bunny.position.y << endl;
    if(bunny.position.x > 16.5 && bunny.position.x < 18 && bunny.position.y < 1.9 && bunny.position.y > 1.6)
    {
        in_tunnel = true;
        shield_on = false;
        bunny.position.x = 17.3;
        bunny.position.y = 2.4;
        angle = 180;
    }
    float phi = 2*PI/360;
    if(in_tunnel)
    {
        if(angle < 180)
        {
            in_tunnel = false;
            // angle = 180;
        }
        if(angle < 360)
        {
            // angle += 0.3;
            bunny.position.y = y + r*sin(phi*angle);
            bunny.position.x = r*cos(phi*angle) + x;
        }
        else if(angle >= 360 )in_tunnel = false;
    }

    double theta;
    for(int i=0;i<3;i++)
    {
        scorr[i].position.x = screen_center_x+3/screen_zoom + 0.3*i;
        scorr[i].position.y = (screen_zoom >= 1.4) ? screen_center_y+3/screen_zoom : screen_center_y + 4/screen_zoom;
    }
    scorr[3].position.y = (screen_zoom >= 1.4) ? screen_center_y+3/screen_zoom : screen_center_y + 4/screen_zoom;
    scorr[3].position.x = scorr[0].position.x - 0.3;
    for(int i=0;i<6;i++)
    {
        levels[i].position.x = screen_center_x-3.5/screen_zoom + 0.3*i;
        levels[i].position.y = (screen_zoom >= 1.4) ? screen_center_y+3/screen_zoom : screen_center_y + 4/screen_zoom;
    }
    live[0].position.x = screen_center_x-3.5/screen_zoom;
    live[0].position.y = (screen_zoom >= 1.4) ? screen_center_y-3/screen_zoom : screen_center_y - 3.5/screen_zoom;
    live[1].position.x = live[0].position.x + 0.1;
    live[1].position.y = (screen_zoom >= 1.4) ? screen_center_y-3/screen_zoom : screen_center_y - 3.5/screen_zoom;
    for(int i=2;i<5;i++)
    {
        live[i].position.x = live[i-1].position.x + 0.3;
        live[i].position.y = live[i-1].position.y;
    }
    live[5].position.x = live[4].position.x + 0.5; 
    live[6].position.x = live[5].position.x + 0.3;
    live[5].position.y = live[4].position.y;
    live[6].position.y = live[4].position.y; 
 
    theta = atan((magnet.position.y-bunny.position.y)/(magnet.position.x-bunny.position.x));
    double dist = sqrt(pow(bunny.position.x-magnet.position.x,2) + pow(bunny.position.y-magnet.position.y, 2));
    if(dist<=3)
    {
        field_on = true;
    }
    else field_on = false;
    if(field_on) 
    {
        bunny.speed += ((bunny.position.x - magnet.position.x < 0) ? 1:-1) * 0.004 * cos(theta);
        bunny.upspeed += ((bunny.position.y - magnet.position.y < 0) ? 1:-1) * 0.004 * sin(theta);
        bunny.g = 0.003;
    }
    else if(!field_on) 
    {
        bunny.speed = bunny.original_speed;
        bunny.g = 0.006;
    }

    if(shield_on) 
    shield = Shield(player_x, player_y);
    // float x1 = bunny.position.x, x2 = magnet.position.x, y1 = bunny.position.y, y2 = magnet.position.y;
    // bunny.speed += ((x2-x1 > 0) ? 1.0 : -1.0) * 0.002 * (abs(x2-x1) / sqrt(pow(x1-x2, 2) + pow(y1-y2, 2)));
    // bunny.upspeed += ((x2-x1 > 0) ? 1.0 : -1.0) * 0.002 * (abs(y2-y1) / sqrt(pow(x1-x2, 2) + pow(y1-y2, 2)));
    // bunny.downspeed -= ((x2-x1 > 0) ? 1.0 : -1.0) * 0.002 * (abs(y2-y1) / sqrt(pow(x1-x2, 2) + pow(y1-y2, 2)));
    float thicc = lasers[0].a / 2;
    bunny_ka_dabba.x = bunny.position.x;
    bunny_ka_dabba.y = bunny.position.y;

    for(int i = 0; i < num_powerups ; i++)
    {
        powerups1[i].tick();
        powerups2[i].tick();
        if(bunny.position.x - powerups1[i].position.x >= 4)
            powerups1[i].far = true;
        if(bunny.position.x - powerups2[i].position.x >= 4)
            powerups2[i].far = true;
    }
    if(level==2)
    {
        for(int i = 0 ; i < num_boomerangs ; i++)
        {
            boomerangs[i].tick();
            if(bunny.position.x - boomerangs[i].position.x >= 2)
            {
                boomerangs[i].turn = true;
                boomerangs[i].flag = 1;
            }
        }
    }
    for(int i=0;i<num_coins;i++)
    {
        if(detect_collision(coins1_ka_dabba[i], bunny_ka_dabba) && !coins1[i].scored)
        {
            score += 5;
            coins1[i].scored = true;
            // cout << "Score = " << score << endl;
        }
        if(detect_collision(coins2_ka_dabba[i], bunny_ka_dabba) && !coins2[i].scored)
        {
            score += 10;
            coins2[i].scored = true;
            // cout << "Score = " << score << endl;
        }
    }
    for(int i=0;i<num_powerups;i++)
    {
        powerups1_ka_dabba[i].x = powerups1[i].position.x;
        powerups1_ka_dabba[i].y = powerups1[i].position.y;
        powerups2_ka_dabba[i].x = powerups2[i].position.x;
        powerups2_ka_dabba[i].y = powerups2[i].position.y;
        if(detect_collision(powerups1_ka_dabba[i], bunny_ka_dabba) && !powerups1[i].scored)
        {
            score += 50;
            powerups1[i].scored = true;
            // cout << "BONUS!! Score is now " << score << endl;
        }
        if(detect_collision(powerups2_ka_dabba[i], bunny_ka_dabba) && !powerups2[i].scored)
        {
            // score += 1000;
            powerups2[i].scored = true;
            lives += 2;
            // cout << "BONUS2!! Speed is increased " << bunny.speed <<endl;
        }
    }
    for(int i=0;i<num_lasers;i++)
    {
        lasers[i].tick();
        if(!in_tunnel)
        {
            lasers1_ka_dabba[i].x = lasers[i].position.x;
            lasers1_ka_dabba[i].y = lasers[i].position.y;
            lasers2_ka_dabba[i].x = lasers[i].position.x + lasers[i].len;
            lasers2_ka_dabba[i].y = lasers[i].position.y;
            lasers3_ka_dabba[i].x = lasers[i].position.x;
            lasers3_ka_dabba[i].y = lasers[i].position.y - lasers[i].gap;
            lasers4_ka_dabba[i].x = lasers[i].position.x + lasers[i].len;
            lasers4_ka_dabba[i].y = lasers[i].position.y - lasers[i].gap;
            if(shield_on)
            {
                if(detect_collision_shield(bunny_ka_dabba, lasers1_ka_dabba[i]) && !lasers[i].injure)
                {
                    lasers[i].injure = true;
                    shield_strength--;
                    if(shield_strength <= 0)
                    {
                        shield_on = false;
                        shield_strength = 10;
                    }
                }
                if(detect_collision_shield(bunny_ka_dabba, lasers2_ka_dabba[i]) && !lasers[i].injure)
                {
                    lasers[i].injure = true;
                    shield_strength--;
                    if(shield_strength <= 0)
                    {
                        shield_on = false;
                        shield_strength = 10;
                    }
                }
                if(detect_collision_shield(bunny_ka_dabba, lasers3_ka_dabba[i]) && !lasers[i].injure)
                {
                    lasers[i].injure = true;
                    shield_strength--;
                    if(shield_strength <= 0)
                    {
                        shield_on = false;
                        shield_strength = 10;
                    }
                }
                if(detect_collision_shield(bunny_ka_dabba, lasers4_ka_dabba[i]) && !lasers[i].injure)
                {
                    lasers[i].injure = true;
                    shield_strength--;
                    if(shield_strength <= 0)
                    {
                        shield_on = false;
                        shield_strength = 10;
                    }
                }
            }
            if(detect_collision(lasers1_ka_dabba[i], bunny_ka_dabba) && !lasers[i].injure)
            {
                lasers[i].injure = true;
                lives--;
            }
            if(detect_collision(lasers2_ka_dabba[i], bunny_ka_dabba) && !lasers[i].injure)
            {
                lasers[i].injure = true;
                lives--;
            }
            if(detect_collision(lasers3_ka_dabba[i], bunny_ka_dabba) && !lasers[i].injure)
            {
                lasers[i].injure = true;
                lives--;
            }
            if(detect_collision(lasers4_ka_dabba[i], bunny_ka_dabba) && !lasers[i].injure)
            {
                lasers[i].injure = true;
                lives--;
            }
            if(bunny.position.x > lasers1_ka_dabba[i].x && bunny.position.x < lasers2_ka_dabba[i].x && !lasers[i].injure) {
                if(abs(bunny.position.y - lasers1_ka_dabba[i].y) - (thicc+0.70) <= 0.05)
                {
                    lasers[i].injure = true;
                    lives--;
                }
                else if(abs(bunny.position.y - lasers3_ka_dabba[i].y) - abs(thicc+0.70) <= 0.05)
                {
                    lasers[i].injure = true;
                    lives--;
                }
            }
        }
    }
    for(int i=0;i<num_boomerangs;i++)
    {
        if(!in_tunnel)
        {
            boomerangs_ka_dabba[i].x = boomerangs[i].position.x;
            boomerangs_ka_dabba[i].y = boomerangs[i].position.y;
            if(detect_collision(boomerangs_ka_dabba[i], bunny_ka_dabba) && !boomerangs[i].injure)
            {
                lives--;
                boomerangs[i].injure = true;
            }
            if(shield_on && detect_collision_shield(bunny_ka_dabba, boomerangs_ka_dabba[i]) && !boomerangs[i].injure)
            {
                boomerangs[i].injure = true;
                shield_strength--;
                if(shield_strength == 0)
                {
                    shield_on = false;
                    shield_strength = 6;
                }
            }
        }
    }
    for(int i=0;i<num_firelines;i++)
    {
        if(!in_tunnel)
        {
            if(shield_on)
            {
                if(detect_collision_shield(bunny_ka_dabba, firelines_ka_dabba1[i]) && !firelines[i].injure)
                {
                    firelines[i].injure = true;
                    shield_strength--;
                    if(shield_strength == 0)
                    {
                        shield_on = false;
                        shield_strength = 6;
                    }
                }
                if(detect_collision_shield(bunny_ka_dabba, firelines_ka_dabba2[i]) && !firelines[i].injure)
                {
                    firelines[i].injure = true;
                    shield_strength--;
                    if(shield_strength == 0)
                    {
                        shield_on = false;
                        shield_strength = 6;
                    }
                }
            }
            if(!firelines[i].injure) 
            {
                if(detect_collision(firelines_ka_dabba1[i], bunny_ka_dabba))
                {
                    firelines[i].injure = true;
                    lives--;
                }
                if(detect_collision(firelines_ka_dabba2[i], bunny_ka_dabba))
                {
                    firelines[i].injure = true;
                    lives--;            
                }
            }
        }
    }
    for(int i=0;i<num_rings;i++)
    {
        rings[i].tick();
        rings_ka_dabba[i].x = rings[i].position.x;
        rings_ka_dabba[i].y = rings[i].position.y;
        if(detect_collision(rings_ka_dabba[i], bunny_ka_dabba) && !rings[i].scored)
        {
            shield_on = true;
            rings[i].scored = true;
        }

    }
    for(int i=0;i<num_jetfires;i++)
    {
        if(zinda_jetfires[i]) {
            // cout << "A" << endl;
            jetfires[i].tick();
            // cout << "B" << endl;
        }
        if(jetfires[i].position.y <= -4 && zinda_jetfires[i]) 
        {
            zinda_jetfires[i] = false; 
        //    jetfires_zinda--;
        //    cout << "jetfires-- count now is " << jetfires_zinda << endl;
        }
    }
    for(int i=0;i<num_iceballs;i++)
    {
        if(zinda_iceballs[i] && !iceballs[i].hit)
        {
            iceballs[i].tick();
            if(iceballs[i].position.y <= -2)
            {
                iceballs[i].hit = true;
                zinda_iceballs[i] = false;
                continue;
            }
            iceballs_ka_dabba[i].x = iceballs[i].position.x;
            iceballs_ka_dabba[i].y = iceballs[i].position.y;
            if(!shield_on)
            {
                if(detect_collision(iceballs_ka_dabba[i], bunny_ka_dabba))
                {
                    iceballs[i].hit = true;
                    zinda_iceballs[i] = false;
                    score -= 2;
                }
            }
            else if(shield_on)
            {
                if(detect_collision_shield(bunny_ka_dabba, iceballs_ka_dabba[i]))
                {
                    shield_strength -= 2;
                    iceballs[i].hit = true;
                    zinda_iceballs[i] = true; 
                    if(shield_strength <= 0)
                    {
                        shield_on = false;
                        shield_strength = 10;
                    }
                }
            }
        }
    }
    for(int i=0;i<num_waterballoons;i++)
    {
        if(zinda_balloons[i] && !waterballoons[i].hit)
        { 
            waterballoons[i].tick();
            if(waterballoons[i].position.y <= -2 || waterballoons[i].position.y >= 4)
            {
                waterballoons[i].hit = true;
                zinda_balloons[i] = false;
                continue;
            }
            waterballoons_ka_dabba[i].x = waterballoons[i].position.x;
            waterballoons_ka_dabba[i].y = waterballoons[i].position.y; 
            for(int j=0;j<num_firelines;j++)
            {
                if(detect_collision(waterballoons_ka_dabba[i], firelines_ka_dabba1[j]) || detect_collision(waterballoons_ka_dabba[i], firelines_ka_dabba2[j]))
                { 
                    // cout << "fireline " << j << " is hit"<<endl;
                    waterballoons[i].hit = true;
                    firelines[j].injure = true;
                    zinda_balloons[i] = false;
                    // balloons_zinda--;
                }
            }
            for(int j=0;j<num_lasers;j++)
            {
                if(detect_collision(lasers1_ka_dabba[j], waterballoons_ka_dabba[i]) && !lasers[j].injure)
                {
                    lasers[j].injure = true;
                    waterballoons[i].hit = true;
                    zinda_balloons[i] = false;
                }
                if(detect_collision(lasers2_ka_dabba[j], waterballoons_ka_dabba[i]) && !lasers[j].injure)
                {
                    lasers[j].injure = true;
                    waterballoons[i].hit = true;
                    zinda_balloons[i] = false;
                }
                if(detect_collision(lasers3_ka_dabba[j], waterballoons_ka_dabba[i]) && !lasers[j].injure)
                {
                    lasers[j].injure = true;
                    waterballoons[i].hit = true;
                    zinda_balloons[i] = false;
                }
                if(detect_collision(lasers4_ka_dabba[j], waterballoons_ka_dabba[i]) && !lasers[j].injure)
                {
                    lasers[j].injure = true;
                    waterballoons[i].hit = true;
                    zinda_balloons[i] = false;
                }
                if(waterballoons_ka_dabba[i].x > lasers1_ka_dabba[j].x && waterballoons_ka_dabba[i].x < lasers2_ka_dabba[j].x && !lasers[j].injure)
                {
                    if(abs(waterballoons_ka_dabba[i].y - lasers1_ka_dabba[j].y) - (thicc+waterballoons_ka_dabba[i].width) <= 0.05)
                    {
                        lasers[j].injure = true;
                        waterballoons[i].hit = true;
                        zinda_balloons[i] = false;
                    }
                    else if(abs(waterballoons_ka_dabba[i].y - lasers3_ka_dabba[j].y) - (thicc+waterballoons_ka_dabba[i].width) <= 0.05)
                    {
                        lasers[j].injure = true;
                        waterballoons[i].hit = true;
                        zinda_balloons[i] = false;
                    }
                }
            }     
        }
    }
    // cout << in_tunnel << " " << bunny.position.x << " " << bunny.position.y << endl;
}

void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    hi        = Hi(0,0.2);
    wall      = Wall(0,0);
    bunny     = Ball (0, -1.8);
    platform  = Platform (-2.5, -4.0); 
    magnet    = Magnet (60, 3);
    scorr[0]  = Score(screen_center_x+3/screen_zoom-2, screen_center_y + 3/screen_zoom);
    scorr[1]  = Score(scorr[0].position.x + 0.3, scorr[0].position.y);
    scorr[2]  = Score(scorr[1].position.x + 0.3, scorr[1].position.y);
    scorr[3]  = Score(scorr[0].position.x - 0.3, scorr[0].position.y);
    levels[0] = Score(screen_center_x-3/screen_zoom-2, screen_center_y + 3/screen_zoom);
    levels[1] = Score(levels[0].position.x + 0.3, levels[0].position.y);
    levels[2] = Score(levels[1].position.x + 0.3, levels[0].position.y);
    levels[3] = Score(levels[2].position.x + 0.3, levels[0].position.y);
    levels[4] = Score(levels[3].position.x + 0.3, levels[0].position.y);
    levels[5] = Score(levels[3].position.x + 0.6, levels[0].position.y);
    live[0]   = Score(screen_center_x-3/screen_zoom-2, screen_center_y - 3/screen_zoom);
    live[1]   = Score(live[0].position.x + 0.3, live[0].position.y);
    live[2]   = Score(live[0].position.x + 0.3, live[0].position.y);
    live[3]   = Score(live[0].position.x + 0.3, live[0].position.y);
    live[4]   = Score(live[0].position.x + 0.3, live[0].position.y);
    live[5]   = Score(live[0].position.x + 0.3, live[0].position.y);
    live[6]   = Score(live[0].position.x + 0.3, live[0].position.y);
    shield    = Shield(-60, 1);
    viserion  = Dragon(45,-2);
    tunnel    = Semicircle(20, 1);

    // coins1
    for(int i = 0; i < num_coins; i++)
        coins1[i] = Coin(i*5 + ((rand() + 0.001)/(RAND_MAX )) * 20, -1 + ((rand() + 0.001)/(RAND_MAX )) * 4, 1);
    // coins2
    for(int i = 0; i < num_coins; i++)
        coins2[i] = Coin(i*8 + ((rand() + 0.001)/(RAND_MAX )) * 30, -2 + ((rand() + 0.001)/(RAND_MAX )) * 4, 0);
    
    
    
    
    
    
    // powerups1
    for(int i = 0; i < num_powerups; i++){
        powerups1[i] = Powerup(((rand() + 0.0001)/(RAND_MAX )) * 1000, 3, 1);
        powerups1[i].speedy = 1.0;
    }
    // powerups2
    for(int i = 0; i < num_powerups; i++){
        powerups2[i] = Powerup(((rand() + 0.0001)/(RAND_MAX )) * 2000, 3, 0);
        powerups2[i].speedy = 1.3;
    }
    // boomerangs
    for(int i = 0; i < num_boomerangs; i++){
        boomerangs[i] = Boomerang(40 + i*30 + (rand() + 0.0001)/(RAND_MAX ) * 10, 3.2);
    }
    // lasers
    for(int i = 0; i < num_lasers; i++){
        lasers[i] = Laser(2 + 13*i + (rand() + 0.0001)/(RAND_MAX ) * 10, ((rand() + 0.001)/RAND_MAX) * 2);
    }
    // fireline
    for(int i = 0; i < num_firelines; i++){
        firelines[i] = Fireline(7 + i*15 + (rand() + 0.0001)/(RAND_MAX ) * 10, ((rand() + 0.001)/RAND_MAX) * 2);
    }
    // rings
    for(int i = 0; i < num_rings; i++){
        rings[i] = Ring(20 + i*10 + (rand() + 0.0001)/(RAND_MAX ) * 20, 1+((rand() + 0.001)/RAND_MAX) * 2);
    }

    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);

    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.5f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


void tick_input(GLFWwindow *window) {
    int A  = glfwGetKey(window, GLFW_KEY_A);
    int D = glfwGetKey(window, GLFW_KEY_D);
    int W = glfwGetKey(window, GLFW_KEY_W);
    int S = glfwGetKey(window, GLFW_KEY_S);
    int K = glfwGetKey(window, GLFW_KEY_K);
    int L = glfwGetKey(window, GLFW_KEY_L);
    // int P = glfwGetKey(window, GLFW_KEY_P);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    // if(P)
    // {
    //     if(!pause) pause = true;
    //     else pause = false;
    // }
    if(abs(viserion.position.x - bunny.position.x - 3) <= 0.5)
    {
        if(tym%5 == 0)
        {
            iceballs[iceballs_zinda%num_iceballs] = Iceball(viserion.position.x-1, viserion.position.y+1.4);
            zinda_iceballs[iceballs_zinda%num_iceballs] = true;
            iceballs[iceballs_zinda%num_iceballs].hit = false;
            iceballs_zinda++;
        }
    }
    // if(P)
        // pause = true;
    if(!in_tunnel)
    {
        if(A) {
            // if(bunny.position.x <= -2.5)
            // {
                // screen_center_x -= bunny.speed;
                // reset_screen();
            // }
            bunny.position.x -= bunny.speed;
        }
        if(D) {
            // if(bunny.position.x >= 2)
            // {
                // screen_center_x += bunny.speed;
                // reset_screen();
            // }
            bunny.position.x += bunny.speed;
        }
        if(W || space) {
            if(tym%3 == 0)
            {
                jetfires[jetfires_zinda%num_jetfires] = Jetfire(bunny.position.x, bunny.position.y-0.55);
                zinda_jetfires[jetfires_zinda%num_jetfires] = true;
                jetfires[jetfires_zinda%num_jetfires].bahar = false;
                jetfires_zinda++;
            }
            jump();
        }
        if(S) {
            if(bunny.position.y > -1)
                bunny.position.y -= 0.04;
        }
        if(K) {
            //
            if(tym%10 == 0)
            {
                waterballoons[balloons_zinda%num_waterballoons] = Waterballoon(bunny.position.x+0.5, bunny.position.y);
                zinda_balloons[balloons_zinda%num_waterballoons] = true;
                waterballoons[balloons_zinda%num_waterballoons].hit = false;
                balloons_zinda++;
            }
        }
        if(L) shield_on = false;
    }
    if(in_tunnel)
    {
        if(D)
        {
            angle += 0.3;
        }
        if(A)
        {
            angle -= 0.3;
        }
        // if(angle < 360)
        // {
        //     angle += 0.3;
        //     bunny.position.y = y + r*sin(phi*angle);
        //     bunny.position.x = r*cos(phi*angle) + x;
        // }
        // else if(angle >= 360 )in_tunnel = false;
    }

    int LEFT  = glfwGetKey(window, GLFW_KEY_LEFT);
    int RIGHT = glfwGetKey(window, GLFW_KEY_RIGHT);
    int UP = glfwGetKey(window, GLFW_KEY_UP);
    int DOWN = glfwGetKey(window, GLFW_KEY_DOWN);

    if(LEFT) {
        screen_center_x-=0.05;
        reset_screen();
    }
    if(RIGHT) {
        screen_center_x+=0.05;
        reset_screen();
    }
    if(UP) {
        screen_center_y+=0.05;
        reset_screen();
    }
    if(DOWN) {
        screen_center_y-=0.05;
        reset_screen();
    }
}

// void tick_input_pause(GLFWwindow *window) {
    // int P = glfwGetKey(window, GLFW_KEY_P);
    // if(P) pause = false;
// }
void sleep_fn(int time)
{
    for(int i=0;i< M * time; i++)
    {
        int a=1;
    }
    return;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 2400;
    int height = 2400;

    window = initGLFW(width, height);

    initGL (window, width, height);
    glfwMakeContextCurrent(window);
    /* Draw in loop */
    glfwSetScrollCallback(window, scroll_callback);    
    
    bunny_ka_dabba.width = 1;
    bunny_ka_dabba.height = 1.4;

    tunnel_ka_dabba.width = 1.5;
    tunnel_ka_dabba.height = 0.02;
    tunnel_ka_dabba.x = tunnel.position.x - tunnel.radius1 - tunnel.radius2;
    tunnel_ka_dabba.y = tunnel.position.y;
    for(int i=0;i<num_coins;i++)
    {
        coins1_ka_dabba[i].width = 2 * coins1[i].radius;
        coins1_ka_dabba[i].height = 2 * coins1[i].radius;
        coins2_ka_dabba[i].width = 2 * coins2[i].radius;
        coins2_ka_dabba[i].height = 2 * coins2[i].radius;
        coins1_ka_dabba[i].x = coins1[i].position.x;
        coins1_ka_dabba[i].y = coins1[i].position.y;
        coins2_ka_dabba[i].x = coins2[i].position.x;
        coins2_ka_dabba[i].y = coins2[i].position.y;
    }
    for(int i=0;i<num_powerups;i++)
    {
        powerups1_ka_dabba[i].width = 2 * powerups1[i].radius;
        powerups1_ka_dabba[i].height = 2 * powerups1[i].radius;
        powerups2_ka_dabba[i].width = 2 * powerups2[i].radius;
        powerups2_ka_dabba[i].height = 2 * powerups2[i].radius;
    }
    for(int i=0;i<num_boomerangs;i++)
    {
        boomerangs_ka_dabba[i].width = 2 * boomerangs[i].radius;
        boomerangs_ka_dabba[i].height = 2 * boomerangs[i].radius;
    }
    for(int i=0;i<num_lasers;i++)
    {
        lasers1_ka_dabba[i].width = 2 * lasers[i].r;
        lasers1_ka_dabba[i].height = 2 * lasers[i].r;
        lasers2_ka_dabba[i].width = 2 * lasers[i].r;
        lasers2_ka_dabba[i].height = 2 * lasers[i].r;        
        lasers3_ka_dabba[i].width = 2 * lasers[i].r;
        lasers3_ka_dabba[i].height = 2 * lasers[i].r;        
        lasers4_ka_dabba[i].width = 2 * lasers[i].r;
        lasers4_ka_dabba[i].height = 2 * lasers[i].r;
    }    
    for(int i=0;i<num_firelines;i++)
    {
        // cout << "Rotation of fireline " << i << " is " << firelines[i].rotation << endl;
        firelines_ka_dabba1[i].width = 2 * firelines[i].a;
        firelines_ka_dabba1[i].height = 2 * firelines[i].a;
        firelines_ka_dabba2[i].width = 2 * firelines[i].a;
        firelines_ka_dabba2[i].height = 2 * firelines[i].a;
        firelines_ka_dabba1[i].x = firelines[i].position.x;
        firelines_ka_dabba1[i].y = firelines[i].position.y;
        firelines_ka_dabba2[i].x = firelines_ka_dabba1[i].x + cos(firelines[i].rotation);
        firelines_ka_dabba2[i].y = firelines_ka_dabba1[i].y + sin(firelines[i].rotation);
    }
    for(int i=0;i<num_rings;i++)
    {
        rings_ka_dabba[i].width = 2 * rings[i].radius2;
        rings_ka_dabba[i].height = 2 * rings[i].radius2;
    }
    
    while (!glfwWindowShouldClose(window) && lives && score >= 0) {
        // cout << pause << endl;
        if (t60.processTick()) {

            jet_pack = false;
            draw();
            glfwSwapBuffers(window);

            tick_elements(bunny.position.x, bunny.position.y);
            jet_pack = false;
            tick_input(window);
            
            char titleString[100];
            if(shield_on){
                sprintf(titleString, "JETPACK JOYRIDE 2.0\t\t\t\tScore: %d\t\t\t\tLives Rem: %d\t\t\t\tShield Strength: %d", score, lives, shield_strength);
            }
            else
                sprintf(titleString, "JETPACK JOYRIDE 2.0\t\t\t\tScore: %d\t\t\t\tLives Rem: %d", score, lives);
            glfwSetWindowTitle(window, titleString);
        }
        // if(pause)
        // {
            // tick_input_pause(window);
        // }
    
        glfwPollEvents();
    }

    quit(window);
}

void jump()
{
    jet_pack = true;
    if(bunny.position.y >= 3.05) {
        bunny.position.y = 3.05;
        return;
    }
    if(bunny.moveDown) {
        bunny.downspeed -= 3*bunny.g;
    }
    bunny.upspeed = bunny.jumpspeed;
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool detect_collision_shield(bounding_box_t player_box, bounding_box_t b)
{
    return (abs(player_box.x - b.x) * 2 < (shield.radius2 + b.width)) &&
           (abs(player_box.y - b.y) * 2 < (shield.radius2 + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;  
    // cout << screen_zoom << endl;  
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
