/// @description Funcion que actualiza la posicion de la Camara

// Posiciones hacia donde se movera la Camara
var xTo,yTo;

// La camara se mueve en direccion al mouse
move_towards_point(mouse_x,mouse_y,0);

// Calculamos la maxima distancia a la que puede alejarse
xTo =object.x + lengthdir_x(min(distancia,distance_to_point(mouse_x,mouse_y)),direction);
yTo =object.y + lengthdir_y(min(distancia,distance_to_point(mouse_x,mouse_y)),direction);

//  Interpolamos entre la posicion actual, y a la direccion que se direige
x = lerp(x,xTo,0.1);
y = lerp(y,yTo,0.1);

// Obtenemos el largo y ancho de la camara
w = camera_get_view_width(view_camera[0]);
h = camera_get_view_height(view_camera[0]);

// Mantenemos la camara centrada en pantalla
camera_set_view_pos(view_camera[0],-floor((w/2))+x,-floor((h/2))+y);
