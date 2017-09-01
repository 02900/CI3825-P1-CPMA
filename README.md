Sistemas Operativos (CI3825) Proyecto 1: Comunicación entre Procesos y Manejo de Archivos

Familiarización con las llamadas al sistema para la creación y acceso a las estructuras del sistema de archivos; y para el envío y recepción de información entre procesos.


Es de gran utilidad en redes UNIX, donde los usuarios tienen asignadas cuotas de disco, contar con una aplicación que recorra recursivamente un árbol de directorios, generando un reporte con la información más importante para cada directorio en el árbol. De esta manera el usuario podrá saber con exactitud en qué directorios está invirtiendo mayor cantidad de espacio.


Este proyecto está enmarcado en el área de los sistemas de archivos y comunicación entre procesos, utilizando las herramientas y llamadas al sistema que han aprendido en las clases de Laboratorio. Se pide desarrollar una aplicación llamada els (enhanced – ls) que debe cumplir con las siguientes características:


<br />• La línea de ejecución de la aplicación será: $ els <output_file> donde el parámetro output_file será el nombre base de los archivos donde se generarán los reportes.
<br />• A partir del directorio donde es ejecutado el comando y para cada directorio a partir de ese punto, deberá aparecer en el reporte la información que se especifica a continuación:
<br />• Path absoluto del directorio Ej: /preg/1/95-27445/
<br />• permisos : todos los permisos actuales del directorio en letras, al igual que son mostrados por el comando ls –l.
<br />• user-id : user id del dueño del directorio.
<br />• group-id : group id asignado al directorio.
<br />• Fecha de la última modificación.
<br />• Fecha del último acceso.
<br />• Número total de archivos contenidos en el directorio (se deben incluir los subdirectorios).
<br />• Número total de bytes ocupados por los archivos ubicados en ese directorio (no incluye
subdirectorios).

<br />• En caso de encontrar un archivo core durante el recorrido, éste será eliminado y agregado al reporte la
información del directorio donde se encontraba el core, su fecha de modificación y el tamaño.
