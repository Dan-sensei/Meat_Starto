# Meat Starto

instalacion:
$ mkdir build
$ cd build
$ cmake ..
$ make -j9

(9) numero de cores + 1


Migracion del proyecto de netbeans a CMAKE.

### Sistemas operativos soportados:
  - Linux
  - Windows (Algun bug)
  - Mac Os X (Sin probar)

# Tareas pendientes
  - Terminar Migrar el motor para que deje de usar SFML y use SDL
  - No se si vale la pena mantener el renderer de SFML, aunque parece muy interesante (con objetivo de aprendizaje), que el juego consiga cambiar de un renderer a otro usando las opciones, en tiempo de ejecución.
  - Implementar Lua (Ya que nos flipamos pues nos flipamos bien)
  

¿Porque usar SDL? 

Sdl es una libreria de mas bajo nivel, es mas compleja de manejar, sin embargo puede que sea mas eficiente.
SFML solo es compatible con win,linux y mac.
Sin embargo SDL tiene ports oficiales y no oficiales en:
linux, mac ,windows, bsd, psp, psvita,ps3,ps4 ,switch ,wii, gamecube, etc


