///scr_initialize_variables(movement_speed,jump_speed,gravity_speed,animation_walk_speed,animation_idle_speed)

/*
    Code Based in Shaun Spalding Tutorial, with some comments ;D
    Some things have been added, like vertical collision with roof, down slopes and animation change

    ~ Leonardo Anez Vladimirovna, Santa Cruz de la Sierra, Bolivia - toborochi98[at]gmail[dot]com
*/

//Variables
movespeed   = argument0;      //Velocidad Movimiento (Caminando)
jumpspeed   = argument1;      //Velocidad de Salto
grav        = argument2;      //Valor de la Gravedad

animation_walk_speed = argument3;
animation_idle_speed = argument4;


image_speed  = animation_walk_speed;
collisionpar = obj_parent_wall;
hsp          = 0;              //Valor Velocidad Horizontal
vsp          = 0;              //Valor Velocidad Vertical
