//------------------------------------------------//
//		Alejandro Cifuentes       	  //
//		 John Haider Giraldo      	  //
//------------------------------------------------//

#include <stdio.h>      
#include <stdlib.h>     
#include <sys/time.h>   
#include <sys/types.h>  
#include <sys/wait.h>   
#include <unistd.h>     

int main(int argc, char *argv[]) {
    if (argc < 2) {				//Verifica argumentos
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);			//imprime como se debe usar el programa y termina con un código de error.
    }
    struct timeval start, end;  		// Estructuras para almacenar el tiempo inicial y final
    gettimeofday(&start, NULL); 		// Obtener el tiempo inicial antes de crear el proceso hijo
    pid_t pid = fork();  			// fork() crea un nuevo proceso (hijo)
    if (pid < 0) {
        perror("fork failed");			// Mensaje de error
        exit(EXIT_FAILURE);			// se sale
    } 
    else if (pid == 0) {
        execvp(argv[1], &argv[1]);		// El proceso hijo ejecuta el comando execvp
        perror("exec failed");			// Imprime mensaje de error
        exit(EXIT_FAILURE);			// termina proceso hijo
    }else {
        int status;
        waitpid(pid, &status, 0);   		// El padre espera a que el hijo termine
        gettimeofday(&end, NULL);   		// Obtener el tiempo final después de que el hijo termina
        // Calcular el tiempo transcurrido en segundos y microsegundos
        double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Elapsed time: %.5f seconds\n", elapsed_time);	// Imprime el tiempo transcurrido
    }
    return 0;
}
