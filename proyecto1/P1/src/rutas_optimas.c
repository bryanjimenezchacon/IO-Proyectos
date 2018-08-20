/************************************************************************
# 
# Instituto Tecnológico de Costa Rica
# Investigación de Operaciones Gr 40
#
#
# Proyecto 0.Menú para Programas de Programación Dinámica
#
# Profesor: Dr.Francisco J.Torres Rojas
#
# Bryan Steve Jiménez Chacón
# Patrick Maynard Gamboa
# Dario Monestel Corella
# 
# II Semestre 2018
# ************************************************************************/
#include <gtk/gtk.h>
#include<stdlib.h>
#include<stdio.h>
#define INF 32767

GtkWidget *scroll , *test, *label, *combo, *mEntrada, *mRespuesta, *gridEntrada, *gridRespuesta, *window, *openDialog, *saveDialog;
GtkEntry *nombresEntradaI[10], *nombresEntradaJ[10], *nombresRespuestaI[10], *nombresRespuestaJ[10];
int nodos = 2;

void crearGrids(){
    gridEntrada = gtk_grid_new();
    gridRespuesta = gtk_grid_new();
    gtk_grid_set_row_spacing (GTK_GRID(gridEntrada), 10);
    gtk_grid_set_column_spacing (GTK_GRID(gridEntrada), 10);
    gtk_grid_set_row_spacing (GTK_GRID(gridRespuesta), 10);
    gtk_grid_set_column_spacing (GTK_GRID(gridRespuesta), 10);

}


//Crea nueva matriz con n*n sacados del slider, y destruye la vieja.
void crearMatriz(GtkWidget *grid, GtkWidget *container, int nodos, int boolean, GtkEntry *nombresI[10], GtkEntry *nombresJ[10]){

    int i, j;
    char value[2];
    
    for (i = 1; i < nodos+1; i++)
    {
        
        for(j = 1; j < nodos+1; j++)
        {             
            if(i==1)
            { 
                sprintf(value, "%c", 64+j);
                GtkWidget *casilla = gtk_entry_new();
                gtk_entry_set_max_length (GTK_ENTRY(casilla), 1);
                gtk_entry_set_width_chars(GTK_ENTRY(casilla),3);
                gtk_entry_set_text(GTK_ENTRY(casilla),value);
                gtk_widget_set_sensitive (casilla,0);
                nombresI[j-1] = GTK_ENTRY(casilla);  
                gtk_grid_attach(GTK_GRID(grid), casilla, 0, j, 1, 1);
                gtk_widget_show (casilla);    
                } 
            if(j==1)
            {
               
                sprintf(value, "%c", 64+i);
                GtkWidget *casilla = gtk_entry_new();
                gtk_entry_set_max_length (GTK_ENTRY(casilla), 1);
                gtk_entry_set_width_chars(GTK_ENTRY(casilla),3);
                gtk_entry_set_text(GTK_ENTRY(casilla),value);
                gtk_widget_set_sensitive (casilla,boolean);
                nombresJ[i-1] = GTK_ENTRY(casilla);
                gtk_grid_attach(GTK_GRID(grid), casilla, i, 0, 1, 1);
                gtk_widget_show (casilla);

                }
            if(i==j)
            {
                GtkWidget *casilla = gtk_entry_new();
                gtk_entry_set_max_length (GTK_ENTRY(casilla), 1);
                gtk_entry_set_width_chars(GTK_ENTRY(casilla),3);
                gtk_entry_set_text(GTK_ENTRY(casilla),"0");
                gtk_grid_attach(GTK_GRID(grid), casilla, i, j, 1, 1);
                gtk_widget_set_sensitive (casilla,0);
                gtk_widget_show (casilla);
                

            }
            else
            {
                GtkWidget *casilla = gtk_entry_new();
                gtk_entry_set_width_chars(GTK_ENTRY(casilla),3);
                gtk_grid_attach(GTK_GRID(grid), casilla, i, j, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(casilla),"*");
                gtk_widget_set_sensitive (casilla,boolean);
                gtk_widget_show (casilla);
            }
        }
    
    }
    gtk_container_add (GTK_CONTAINER (container), grid);
    gtk_widget_show (grid);

}

//Destruye las matrices y libera la memoria.
void destruirMatriz(GtkWidget *container)
{

    GList *hijos;
    hijos = gtk_container_get_children(GTK_CONTAINER(container));
    int tamanho = g_list_length(hijos);
    for(int i = 0; i != tamanho; i++){
        gtk_widget_destroy(GTK_WIDGET(g_list_nth(hijos, i)->data));        
    }
    g_list_free(hijos);
}

//Signal del scroll. Cada vez que cambia de valor crea una matriz de tamaño valor x valor.

int on_scroll_value_changed(GtkScale *scale){

    destruirMatriz(mEntrada);
    destruirMatriz(mRespuesta);
    nodos = (int)gtk_range_get_value(GTK_RANGE(scale));
    crearGrids();
    crearMatriz(gridEntrada, mEntrada, nodos, 1, nombresEntradaI, nombresEntradaJ);
    crearMatriz(gridRespuesta, mRespuesta,nodos, 0, nombresRespuestaI, nombresRespuestaJ);

    
    

}
void terminar() {
    //gtk_main_quit();
}




void floyd(int nodos){

    //Inicializar dos matrices nodos*nodos llenas de infinitos para algoritmo y respuesta
    int** mFloyd;
    int** mRespuesta;
    mFloyd = malloc(nodos*sizeof(int*));
    mRespuesta = malloc(nodos*sizeof(int*));

    for(int m=0;m<nodos;m++)
    {
        mFloyd[m] = malloc(nodos * sizeof(int));
        mRespuesta[m] = malloc(nodos * sizeof(int));

        for(int n=0;n<nodos;n++)
        {
            mFloyd[m][n] = INF;
            mRespuesta[m][n] = INF;
        }
    }

    //Rellenar matriz con datos de usuario
    
    //Floyd
    for(int k=0;k<nodos;k++)
    {
        for(int i=0;i<nodos;i++)
        {
            for(int j=0;j<nodos;j++)
            {
                int temp = mFloyd[i][k] + mFloyd[k][j];
                if(mFloyd[i][j] > temp)
                {
                    mFloyd[i][j] = temp;
                    mRespuesta[i][j] = k;
                }
            }
        }
    }   
}

//Devuelve el nombre del nodo cambiado al original 
void copiarNombres()
{
    for(int i = 0; i < nodos; i++)
    {
        gtk_entry_set_text(nombresEntradaJ[i], gtk_entry_get_text(nombresRespuestaJ[i]));
    }

}

//Chequea si el nombre ingresado para el nodo es válido. Sólo se aceptan letras mayúsculas o minúsculas
int chequearLetras(){

    for(int i = 0; i < nodos; i++)
    {
        
        int temp = (int) gtk_entry_get_text(nombresEntradaJ[i])[0];

        if(temp < 65 | temp > 122)
        {
            return 0;
        }
    }
    return 1;
}

//Chequea que no haya nombres repetidos en los nodos
int buscarRepetidos(){

    for(int i = 0; i< nodos; i++)
    {
        for(int j = 0; j < nodos; j++)
        {
            if(j != i)
            {
                if(gtk_entry_get_text(nombresEntradaJ[i])[0] == gtk_entry_get_text(nombresEntradaJ[j])[0])
                {   
                    return 0;
                }
            }
            
        }
    }
    return 1;
}


//Salva el nombre de los nodos.
void button_pressed(){
    

    if(chequearLetras() & buscarRepetidos())
    {
        for(int i = 0; i < nodos; i++)
        {
        gtk_entry_set_text(nombresRespuestaJ[i], gtk_entry_get_text(nombresEntradaJ[i]));
        gtk_entry_set_text(nombresRespuestaI[i], gtk_entry_get_text(nombresEntradaJ[i]));
        gtk_entry_set_text(nombresEntradaI[i], gtk_entry_get_text(nombresEntradaJ[i]));
        }
    }
    else
    {
        copiarNombres();
    }

    
    

}

void SignalSalir()
{
    gtk_widget_destroy(GTK_WIDGET(window));
}

void SignalAbrir(gpointer window)
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new ("Abrir archivo", GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    gtk_widget_show_all(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
    {
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    }
    else
    {
        g_print("Cancel");
    }
    gtk_widget_destroy(dialog);
}

void SignalSalvar()
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new ("Salvar archivo", GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_SAVE,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    gtk_widget_show_all(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
    {
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    }
    else
    {
        g_print("Cancel");
    }
    gtk_widget_destroy(dialog);

}

void OpenDialog_Cancelar()
{
    gtk_widget_destroy(GTK_WIDGET(openDialog));
}

void SaveDialog_Cancelar()
{
    gtk_widget_destroy(GTK_WIDGET(saveDialog));
}

int main(int argc, char *argv[])
{

    GtkBuilder      *builder; 
    

 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/rutas_optimas.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "rutas"));
    gtk_builder_connect_signals(builder, NULL);

    scroll = GTK_WIDGET(gtk_builder_get_object(builder, "scroll"));
    test = GTK_WIDGET(gtk_builder_get_object(builder, "test"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    combo = GTK_WIDGET(gtk_builder_get_object(builder, "combo"));
    mEntrada = GTK_WIDGET(gtk_builder_get_object(builder, "mEntrada"));
    mRespuesta = GTK_WIDGET(gtk_builder_get_object(builder, "mRespuesta"));

    crearGrids();
    crearMatriz(gridEntrada, mEntrada, 2, -1, nombresEntradaI, nombresEntradaJ);
    crearMatriz(gridRespuesta, mRespuesta,2, 0, nombresRespuestaI, nombresRespuestaJ);




    g_object_unref(builder);    
    gtk_widget_show(window);                
    gtk_main();

    
 
    return 0;
} 
 


