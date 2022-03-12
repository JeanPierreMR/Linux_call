# Linux_call

Luego de revisar en clase cómo funcionan los system calls, creamos un repositorio para explicar cómo añadir un system call propio al kernel y hacer una prueba de este. Todos los archivos mencionados se encuentran en este mismo repositorio. 

### 1. Configurar la máquina virtual 
Se utilizó Ubuntu en Oracle VM Virtualbox con 4 cores para configurar el ambiente. Iniciando con encender la máquina virtual y acceder a la terminal. 

### 2. Código fuente Kernel
Se revisó la versión del Kernel de Linux usando el comando: uname -r. En nuestro caso, la versión era la 4.4.0. Luego, se busca en este sitio https://mirrors.edge.kernel.org/pub/linux/kernel/ el archivo .xz correspondiente a la versión a descargar. Nosotros descargamos la versión versión 16.04.01. 
El comando utilizado se veía así:
```
wget -P ~/ https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-16.04.01.tar.xz
```

Ahora se debe descomprimir y reiniciar su máquina virtual. Esto se lleva a cabo con el siguiente comando:
```
sudo tar -xvf linux-16.04.01.tar.xz -C ~/ && reboot
```

### 3. Definición de un nuevo system call
Se creo un directorio llamado custom_calls con los siguientes comandos:
```
mkdir custom_calls
```
En este directorio se creo un archivo llamado check_complete con el siguiente comando: 
```
gedit check_complete.c
```
![image](https://user-images.githubusercontent.com/48104764/157766672-e65eece6-5e83-4aab-9ca9-01319ee80540.png)
Luego de esto, en el mismo directorio, creamos un archivo llamado Makefile para asegurar que el archivo check_complete-c sea compilado e incluido en el código fuente del Kernel:
```
gedit Makefile
```
En este archivo, buscamos "core-y" en el documento y agregamos custom_calls/ al final de esta linea:
```
core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ custom_calls/
```
Esto fue agregado para especificarle al compilador que los archivos fuente de nuestra nueva llamada dde sistema están presentes en el directorio custom_calls.
![image](https://user-images.githubusercontent.com/48104764/157767115-314c6672-4c2f-41c5-8e7f-d516965d9ce7.png)


### 4. Configuración del Kernel
Utilizaremos sudo -i para no usar sudo en cada comando. 

Luego cambiaremos al directorio con la carpeta dónde se encuentra el Kernel desempaquetado:
```
cd linux-16.04.01.tar.xz
```

Agregamos una llamada al sistema personalizada a la tabla de system calls. En nuestro caso, en base a la arquitectura de la máquina, utilizamos:
```
gedit arch/x86/entry/syscalls/syscall_64.tbl
```

En este archivo, agregamos una linea (329) luego del último tipo common en el syscall, con nuestra llamada al sistema:
```
329     common     check_complete       sys_check_complete 
```
![image](https://user-images.githubusercontent.com/48104764/157764538-f246aa5d-b786-4788-8af3-48d1fff2a0cf.png)

Luego de esto, agregamos un prototipo de función para cada una al archivo de encabezado: 
```
subl include/linux/syscalls.h
```
Al final de este archivo antes del ```endif``` agregamos:
```
asmlinkage  long  sys_check_compete(char *exp);
```
![image](https://user-images.githubusercontent.com/48104764/157765496-32e80e2b-62cf-4761-908f-856389d2b9c7.png)
La etiqueta asmlinkage es un #define que le dice al compilador que la función no debe esperar encontrar ninguno de sus argumentos en los registros, sino solo en el stack del CPU.

### 4. Compilar el Kernel
Por último, para configurar el Kernel utilizamos el siguiente comando:
```
make menuconfig
```
Aparecerá una pestaña con opciones de configuración pero no realizamos cambios, sino que lo mantuvimos en la configuración predeterminada. 

Para compilar el Kernel usaremos el siguiente comando:
```
sudo make -j4
```
El -j4 es utilizado para acelerar el proceso aprovechando los cores configurados en la máquina virtual. 

### 4. Instalar el Kernel
Para la instalacións se utilizó el comando: 
```
sudo make modules_install install
```
![image](https://user-images.githubusercontent.com/48104764/157768759-0050255e-acba-487e-9316-9777cbc13503.png)

Para actualizar el Kernel se reinició la máquina virtual.

Luego de reiniciar verificamos la versión de kernel con el comando utilizado anteriormente:
```
uname -r
```
### 5. Probar la llamada al sistema
Para probar utilizamos las siguientes funciones: 
```
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
	char exp[100];
	double result;
	scanf("%s", exp);
	char *x = exp;
	// Function call
	if (syscall(329, x))
	{
	printf("Balanced \n");
	}
	else
	printf("Not Balanced \n");
	return 0;
}
```
![image](https://user-images.githubusercontent.com/48104764/157782695-243447ba-21a7-44db-9f36-6d8791f3fee6.png)


