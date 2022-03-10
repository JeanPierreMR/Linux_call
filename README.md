# Linux_call

Luego de revisar en clase cómo funcionan los system calls, creamos un repositorio para explicar cómo añadir un system call propio al kernel y hacer una prueba de este. Todos los archivos mencionados se encuentran en este mismo repositorio. 

##1. Configurar la máquina virtual 
Se utilizó Ubuntu en Oracle VM Virtualbox con 4 cores para configurar el ambiente. Iniciando con encender la máquina virtual y acceder a la terminal. 

##2. Código fuente Kernel
Se revisó la versión del Kernel de Linux usando el comando: uname -r. En nuestro caso, la versión era la 4.4.0. Luego, se busca en este sitio https://mirrors.edge.kernel.org/pub/linux/kernel/ el archivo .xz correspondiente a la versión a descargar. Nosotros descargamos la versión versión 16.04.01. 
El comando utilizado se veía así:
wget -P ~/ https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-16.04.01.tar.xz

Ahora se debe descomprimir y reiniciar su máquina virtual. Esto se lleva a cabo con el siguiente comando:
sudo tar -xvf linux-16.04.01.tar.xz -C ~/ && reboot

##3. Configuración del Kernel


