/*1.Desarrollar una interfaz por consola donde se solicite al usuario la cantidad de clientes.
 2.Solicitar al usuario la cargadelos clientescreados dinámicamente en el paso anterior.
 3.A medida que se dé de alta cada cliente, Generar aleatoriamente la cantidad de productos asociados al cliente ysus características.
 Ej:producto cargado nro. 2
 Producto
 {
    ProductoID=2;
    Cantidad= 1;
    *TipoProducto = “Snack”;
    PrecioUnitario= 100;
}
 4.Implemente una función que calcule el costo total de un producto.Esta funcióndebe recibir como parámetro el producto y 
 devolver el resultado de calcular laCantidad por elPrecioUnitario.
 5.Mostrar  por  pantalla  todo  lo  cargado.  Incluyendo un  total  a  pagar  por  cliente (sumatoria del costo de todos los productos)*/
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

int main() {
    srand(time(NULL)); 
    int cant_clientes;
    T_Cliente *Nuevo_Cliente = (T_Cliente*)malloc(sizeof(T_Cliente));
   
    printf("Ingrese la cantidad de clientes(entre 1 y 5): \n"); scanf("%d",&cant_clientes);
    //FALTA EL CONTROL ESCTRICTO DE CANTIDAD CLIENTES//  
    CargaCliente(Nuevo_Cliente, cant_clientes);
    MostrarCliente(Nuevo_Cliente,cant_clientes);
    scanf(" %c");
   // free(Nuevo_Cliente);
    return 0;
}

//FUNCIONES//
int aleatorio(int min,int max){
    return min + rand() % (max-min+1);
}
void CargaCliente(T_Cliente *cliente, int cant_clientes)  //
{   
    //for (int i = 0; i < cant_clientes; i++)
   // {
        char aux[tama]; //Guardo lo ingresado por pantalla
        printf("Ingrese el nombre del cliente N°"); scanf("%s",aux);
        cliente->NombreCliente = (char *)malloc(strlen(aux)+1 * sizeof(char)); //Devuelve el tamaño de la cadena + el caracter de escape
        strcpy(cliente->NombreCliente,aux);
        cliente->CantidadProductosAPedir = aleatorio(1,5);
        cliente->Productos = (T_Producto *)malloc(cliente->CantidadProductosAPedir * sizeof(T_Producto)); //Reserva para struc productos
        CargaProducto(cliente->Productos,cliente->CantidadProductosAPedir);
   // }
}
void CargaProducto(T_Producto *productos,int cant_productos)
{
    for (int i = 0; i < cant_productos; i++)
    {
        (productos + i)->ProductoID = i+1;
        (productos + i)->Cantidad = aleatorio(1,5);
        (productos + i)->TipoProducto = (char*)malloc(15*sizeof(char)); 
        strcpy((productos + i)->TipoProducto,ListaProductos[aleatorio(0,4)]);
        (productos + i)->PrecioUnitario =(float)aleatorio(10,100);
    }
}
void MostrarCliente(T_Cliente *cliente, int cant_clientes)
{
    for (int i = 0; i < cant_clientes; i++)
    {
        printf("Cliente N: %d\n",(cliente + i)->ClienteID);
        printf("Nombre: %s\n",(cliente + i)->NombreCliente);
        printf("Cantidad de productos solicitados: %d\n",(cliente + i)->CantidadProductosAPedir);
        for (int j = 0; j < cliente->CantidadProductosAPedir; j++)
        {
            printf("ID del producto: %d\n",(cliente + i)->Productos[j]->ProductoID); //FALTA PONER CORRECTAMENTE EL ID para que se asocie al prod
            printf("Stock: %d\n",(cliente + i)->Productos->Cantidad);
            printf("Producto: %c\n",(cliente + i)->Productos->TipoProducto);//queda pendiente el tipo hasta que use enum//
            printf("Precio Unitario: %.2f\n",(cliente + i)->Productos->PrecioUnitario);
        }
    }
}
