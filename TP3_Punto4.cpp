#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int tama = 50; //tamaño para aux del nombre
const char *ListaProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

typedef struct
{
    int ProductoID;//Numerado en ciclo iterativo
    int Cantidad;// entre 1 y 10
    char *TipoProducto;//Algún valordel arreglo ListaProductos 
    float PrecioUnitario;// entre 10 -100
}T_Producto;
typedef struct
{
    int ClienteID;// Numerado en el ciclo iterativo
    char *NombreCliente;// Ingresado por usuario
    int CantidadProductosAPedir;// (alteatorio entre 1 y 5)
    T_Producto *Productos; //El tamaño de este arreglo depende de la variable// “CantidadProductosAPedir" 
}T_Cliente;

//PROTO//
int aleatorio(int min,int max);
void CargaCliente(T_Cliente *cliente, int cant_clientes);
void CargaProducto(T_Producto *productos,int cant_productos);
void MostrarCliente(T_Cliente *cliente, int cant_clientes);
float Costo_total(T_Producto *cliente);

int main() {
    srand(time(NULL)); 
    int cant_clientes;
    T_Cliente *Nuevo_Cliente;
   
    printf("Ingrese la cantidad de clientes(entre 1 y 5): \n"); scanf("%d",&cant_clientes);
    Nuevo_Cliente = (T_Cliente*)malloc(cant_clientes * sizeof(T_Cliente));
    //FALTA EL CONTROL ESCTRICTO DE CANTIDAD CLIENTES//  
    CargaCliente(Nuevo_Cliente, cant_clientes);
    MostrarCliente(Nuevo_Cliente,cant_clientes);
    scanf(" %c");
    free(Nuevo_Cliente);
    return 0;
}

//FUNCIONES//
int aleatorio(int min,int max){
    return min + rand() % (max-min+1);
}
void CargaCliente(T_Cliente *cliente, int cant_clientes) 
{   
    for (int i = 0; i < cant_clientes; i++)
    {
        char aux[tama]; //Guardo lo ingresado por pantalla
        (cliente + i)->ClienteID = i+1;
        printf("Ingrese el nombre del cliente N%d: ",i+1); scanf("%s",aux);
        (cliente + i)->NombreCliente = (char *)malloc(strlen(aux)+1 * sizeof(char)); //Devuelve el tamaño de la cadena + el caracter de escape
        strcpy((cliente + i)->NombreCliente,aux);
        (cliente + i)->CantidadProductosAPedir = aleatorio(1,5);
        (cliente + i)->Productos = (T_Producto *)malloc((cliente + i)->CantidadProductosAPedir * sizeof(T_Producto)); //Reserva para struc productos
        CargaProducto((cliente + i)->Productos,(cliente + i)->CantidadProductosAPedir);
    }
}
void CargaProducto(T_Producto *productos,int cant_productos)
{
    for (int i = 0; i < cant_productos; i++)
    {
        int aux_id = aleatorio(1,5); //Para relacionar el ID con LISTAPRODUCTOS
        (productos + i)->ProductoID = aux_id;
        (productos + i)->Cantidad = aleatorio(1,5);
        (productos + i)->TipoProducto = (char*)malloc(20*sizeof(char)); 
        strcpy((productos + i)->TipoProducto,ListaProductos[aux_id]);
        (productos + i)->PrecioUnitario =(float)aleatorio(10,100);
    }
}
void MostrarCliente(T_Cliente *cliente, int cant_clientes)
{
    
    for (int i = 0; i < cant_clientes; i++)
    {
        float aux_total = 0; //Inicializar en 0 cada  vez que entra nuevo cliente
        printf("Cliente N: %d\n",(cliente + i)->ClienteID);
        printf("Nombre: %s\n",(cliente + i)->NombreCliente);
        printf("Cantidad de productos solicitados: %d\n",(cliente + i)->CantidadProductosAPedir);
        for (int j = 0; j < (cliente + i)->CantidadProductosAPedir; j++)
        {
            printf("ID del producto: %d\n",((cliente+i)->Productos + j)->ProductoID);  
            printf("Cantidad: %d\n",((cliente+i)->Productos + j)->Cantidad);
            printf("Producto: %s\n",((cliente+i)->Productos + j)->TipoProducto);
            printf("Precio Unitario: %.2f\n",((cliente+i)->Productos + j)->PrecioUnitario);
            aux_total = aux_total + Costo_total((cliente+i)->Productos+j);
        }
        printf("El costo total de los productos es: %.3f\n",aux_total);
        printf("-------------------------------------------\n");
    }
}
float Costo_total(T_Producto *producto)
{
    return producto->Cantidad * producto->PrecioUnitario;
}