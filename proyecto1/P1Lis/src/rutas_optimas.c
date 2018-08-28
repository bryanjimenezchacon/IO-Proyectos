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

/* Determines if to continue the timer or not */
static gboolean continue_timer = FALSE;

/* Determines if the timer has started */
static gboolean start_timer = FALSE;

/* Display seconds expired */
static int sec_expired = 0;

GtkWidget *image;
GtkWidget *scroll , *label, *siguiente, *mEntrada, *mRespuesta, *gridEntrada, *gridRespuesta, *mTablasP, *gridTablasP, *cerrarTablasP, *window, *windowTablas, *windowGrafo, *buttonTablasP, *openDialog, *saveDialog, *resultado, *window_aux, *buttonRutas, *comboBoxText_Partida, *comboBoxText_Destino, *rutas_resultado;
GtkEntry *nombresEntradaI[10], *nombresEntradaJ[10], *nombresRespuestaI[10], *nombresRespuestaJ[10];
int** matrizEntrada;
int** matrizRespuesta;
int nodos = 2, k = 0;
char* nombres;

void crearGrids(){
    gridEntrada = gtk_grid_new();
    gridRespuesta = gtk_grid_new();
    gridTablasP = gtk_grid_new();
    gtk_grid_set_row_spacing (GTK_GRID(gridEntrada), 10);
    gtk_grid_set_column_spacing (GTK_GRID(gridEntrada), 10);
    gtk_grid_set_row_spacing (GTK_GRID(gridRespuesta), 10);
    gtk_grid_set_column_spacing (GTK_GRID(gridRespuesta), 10);
    gtk_grid_set_row_spacing (GTK_GRID(gridTablasP), 10);
    gtk_grid_set_column_spacing (GTK_GRID(gridTablasP), 10);

}

//Crea una matriz de ints en memoria
int** inicializarMatriz(int nodos, int x)
{
    int** matriz;
    matriz = calloc(nodos,sizeof(int*));

    for(int m=0;m<nodos;m++)
    {
        matriz[m] = calloc(nodos, sizeof(int));

        for(int n=0;n<nodos;n++)
        {
            matriz[m][n] = x;
        }
    }
    return matriz;
}

void digraphVacia()
{
    FILE *file, *fRuta;
    file = fopen("grafo.dot", "w");
    fprintf(file, "%s\n", "digraph G {");
    const gchar *nodoPartida;
    for(int i = 0; i < nodos; i++)
    {
        nodoPartida = gtk_entry_get_text(GTK_ENTRY(nombresEntradaJ[i]));
        fprintf(file, "%s\n", nodoPartida);
    }

    fprintf(file, "%s", "}");    
    fclose(file);
}

void digraph(int boolean, char ruta[160])
{
    FILE *file, *fRuta;
    file = fopen("grafo.dot", "w");
    fRuta = fopen("ruta.dot", "w");
    fprintf(file, "%s\n", "digraph G {");
    if(boolean)
    {
        fprintf(fRuta, "%s\n", "digraph G {");
    }

    //a -> b[label="0.2"];
    const gchar *nodoPartida, *nodoDestino;
    //pointer = gtk_entry_get_text(GTK_ENTRY(z));

    for(int i = 0; i < nodos; i++)
    {
        for(int j = 0; j < nodos; j++)
        {
            if(matrizEntrada[i][j] != 0 && matrizEntrada[i][j] != INF)
            {
                nodoPartida = gtk_entry_get_text(GTK_ENTRY(nombresEntradaJ[i]));
                nodoDestino = gtk_entry_get_text(GTK_ENTRY(nombresEntradaJ[j]));
                fprintf(file, "\t%s %s %s%s%d%s\n", nodoPartida, "->", nodoDestino, "[label=\"",matrizEntrada[i][j], "\"];");
                if(boolean){
                    fprintf(fRuta, "\t%s %s %s%s%d%s\n", nodoPartida, "->", nodoDestino, "[label=\"",matrizEntrada[i][j], "\"];");
                }
                
            }               
        }
    }
    if(boolean){
    	g_print(ruta);
        strtok(ruta, "");
        g_print(ruta);
        fprintf(file , "%s", ruta);
        fclose(fRuta);
    }
    fprintf(file, "%s", "}");    
    fclose(file);

    

}

void crearMatrizP()
{
    char c[2];
    for(int i = 1; i < nodos+1; i++)
    {
        for(int j = 1; j < nodos + 1; j++)
        {
            if(i==1)
            {
                GtkWidget *label = gtk_label_new(gtk_entry_get_text(nombresEntradaJ[j-1]));
                gtk_label_set_width_chars(GTK_LABEL(label), 3);
                gtk_grid_attach(GTK_GRID(gridTablasP), label, 0, j, 1, 1);
                gtk_widget_show (label);
            }
            if(j==1)
            {
                GtkWidget *label = gtk_label_new(gtk_entry_get_text(nombresEntradaJ[i-1]));
                gtk_label_set_width_chars(GTK_LABEL(label), 3);
                gtk_grid_attach(GTK_GRID(gridTablasP), label, i, 0, 1, 1);
                gtk_widget_show (label);
            }
                        
            GtkWidget *label = gtk_label_new("");   
            gtk_label_set_width_chars(GTK_LABEL(label), 3);
            sprintf(c, "%c", matrizRespuesta[i-1][j-1]+48);
            gtk_label_set_text(GTK_LABEL(label),c);
            gtk_grid_attach(GTK_GRID(gridTablasP), label, i, j, 1, 1);
            gtk_widget_show (label);            
            
        }
    }
    gtk_container_add (GTK_CONTAINER (mTablasP), gridTablasP);
    gtk_widget_show (gridTablasP);
}




//Crea nueva matriz con n*n sacados del slider, y destruye la vieja.
void crearMatriz(GtkWidget *grid, GtkWidget *container, int nodos, int boolean, GtkEntry *nombresI[10], GtkEntry *nombresJ[10]){

    int i, j;
    char value[2];
    k = 0;
    gtk_widget_set_sensitive (siguiente,1);
    gtk_button_set_label(GTK_BUTTON(siguiente), "Resolver");
    gtk_label_set_text(GTK_LABEL(resultado), "Resultado"); 
    
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
                //gtk_entry_get_text(gtk_grid_get_child_at(gridEntrada,0,0));
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
    destruirMatriz(mTablasP);
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(comboBoxText_Partida));
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(comboBoxText_Destino));
    gtk_widget_set_sensitive(buttonRutas, 0);
    nodos = (int)gtk_range_get_value(GTK_RANGE(scale));
    nombres = calloc(nodos,sizeof(const char));
    crearGrids();
    crearMatriz(gridEntrada, mEntrada, nodos, 1, nombresEntradaI, nombresEntradaJ);
    crearMatriz(gridRespuesta, mRespuesta,nodos, 0, nombresRespuestaI, nombresRespuestaJ);
    matrizRespuesta = inicializarMatriz(nodos, 0);
    crearMatrizP();
    digraphVacia();
}

void limpiar(){

    destruirMatriz(mEntrada);
    destruirMatriz(mRespuesta);
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(comboBoxText_Partida));
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(comboBoxText_Destino));
    gtk_widget_set_sensitive(buttonRutas, 0);
    crearGrids();
    crearMatriz(gridEntrada, mEntrada, nodos, 1, nombresEntradaI, nombresEntradaJ);
    crearMatriz(gridRespuesta, mRespuesta,nodos, 0, nombresRespuestaI, nombresRespuestaJ);
    matrizRespuesta = inicializarMatriz(nodos, 0);
    crearMatrizP();
}

void terminar() 
{
    //gtk_main_quit();
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




void SignalSalir()
{
    gtk_widget_destroy(GTK_WIDGET(window));
}


void guardar(char* archivo)
{
    GtkWidget *z;
    FILE *file;
    file = fopen(archivo, "w");
    fprintf(file, "%i\n", nodos);

    for(int j = 1; j<nodos+1; j++)
    {
        z = gtk_grid_get_child_at(GTK_GRID(gridEntrada),0,j);
        const gchar *pointer;
        pointer = gtk_entry_get_text(GTK_ENTRY(z));
        fprintf(file, "%s", pointer);
        fprintf(file, "%s\n", "");
    }

    for(int i = 1; i<nodos+1; i++)
    {
        for(int j = 1; j<nodos+1; j++)
        {
            z = gtk_grid_get_child_at(GTK_GRID(gridEntrada),j,i);
            const gchar *pointer;
            pointer = gtk_entry_get_text(GTK_ENTRY(z));
            char c = gtk_entry_get_text(GTK_ENTRY(z))[0];
            if(c == 42){
                fprintf(file, "%i", INF);
                fprintf(file, "%s\n", "");
            }
            else
            {
                int x = atoi(pointer);
                fprintf(file, "%i", x);
                fprintf(file, "%s\n", "");
            }
            

        }
    }

    fclose(file);
}

//Pasa los datos ingresados por el usuario a la matriz en memoria
void anhadirInput(int** matriz)
{
    GtkWidget *z;
    for(int i = 1; i < nodos+1; i++){
        for(int j = 1; j < nodos+1; j++)
        {
            z = gtk_grid_get_child_at(GTK_GRID(gridEntrada),j,i);
            if(gtk_entry_get_text(GTK_ENTRY(z))[0] != '*'){
                const gchar *g; 
                g = gtk_entry_get_text(GTK_ENTRY(z));
                int x = g_ascii_strtoll(g, NULL,10);
                matriz[i-1][j-1] = x;
            }
            
        }
        

    }

}

void abrir(char* archivo)
{    
    limpiar();
    FILE *file;
    file = fopen(archivo, "r");
    char c[10];
    fgets(c, sizeof(c), file);
    nodos = atoi(c);
    nombres = calloc(nodos,sizeof(const char));

    destruirMatriz(mEntrada);
    destruirMatriz(mRespuesta);
    destruirMatriz(mTablasP);
    crearGrids();
    crearMatriz(gridEntrada, mEntrada, nodos, 1, nombresEntradaI, nombresEntradaJ);
    crearMatriz(gridRespuesta, mRespuesta,nodos, 0, nombresRespuestaI, nombresRespuestaJ);
    matrizRespuesta = inicializarMatriz(nodos, 0);
    crearMatrizP();

    for(int i = 1; i < nodos+1; i++)
    {
        fgets(c, sizeof(c), file);
        GtkWidget *z, *y;
        nombres[i-1] = c[0];
        z = gtk_grid_get_child_at(GTK_GRID(gridEntrada),0,i);
        y = gtk_grid_get_child_at(GTK_GRID(gridEntrada),i,0);
        gtk_entry_set_text(GTK_ENTRY(z),c);
        gtk_entry_set_text(GTK_ENTRY(y),c);
        z = gtk_grid_get_child_at(GTK_GRID(gridRespuesta),0,i);
        y = gtk_grid_get_child_at(GTK_GRID(gridRespuesta),i,0);
        gtk_entry_set_text(GTK_ENTRY(z),c);
        gtk_entry_set_text(GTK_ENTRY(y),c);
    }

    for(int i = 1; i < nodos+1; i++)
    {
        for(int j = 1; j< nodos+1; j++)
        {
            fgets(c, sizeof(c), file);
            GtkWidget *z;
            z = gtk_grid_get_child_at(GTK_GRID(gridEntrada),j,i);          
            strtok(c, "\n");
            int x = atoi(c);
            if(x == INF){
                gtk_entry_set_text(GTK_ENTRY(z),"*");
            }
            else
            {
                gtk_entry_set_text(GTK_ENTRY(z),c);
            }
            
            
        }
    }
    matrizEntrada = inicializarMatriz(nodos, INF);
    matrizRespuesta = inicializarMatriz(nodos, 0);
    anhadirInput(matrizEntrada);
    digraph(0,NULL);
    fclose(file);
}


void SignalAbrir(gpointer window)
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new ("Abrir archivo", GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    gtk_widget_show_all(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
    {
        abrir(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
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
        guardar(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
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



void imprimirMatriz(int** matriz)
{
    for(int i = 0; i<nodos; i++)
    {
        g_print("%s\n", "");
        for(int j = 0; j<nodos; j++)
        {
            g_print("%i ", matriz[i][j]);
        }
    }
}


//Muestra el resultado en la matriz de resultado
void pasarResultado(int** matriz)
{
    GtkWidget *z, *y;
    char c[20], s[2];
    //destruirMatriz(mTablasP);
    //crearMatrizP();
    for(int i = 1; i<nodos+1; i++)
    {
        for(int j = 1; j<nodos+1; j++)
        {
            z = gtk_grid_get_child_at(GTK_GRID(gridRespuesta),j,i);
            sprintf(c, "%d", matriz[i-1][j-1]);
            y = gtk_grid_get_child_at(GTK_GRID(gridTablasP),j,i);
            sprintf(s, "%c", matrizRespuesta[i-1][j-1]+48);
            
            if(matriz[i-1][j-1] == INF){
                gtk_entry_set_text(GTK_ENTRY(z),"*");
            }
            else
            {
                gtk_entry_set_text(GTK_ENTRY(z),c);
                if(matrizRespuesta[i-1][j-1]+48 == ':'){
                    gtk_label_set_text(GTK_LABEL(y),"10");
                }
                else
                {
                    gtk_label_set_text(GTK_LABEL(y),s);
                }
                
            }
            
        }
    }
}







void floyd(int nodos)
{
    
    //Floyd
        for(int i=0;i<nodos;i++)
        {
            for(int j=0;j<nodos;j++)
            {
                int temp = matrizEntrada[i][k] + matrizEntrada[k][j];
                if(matrizEntrada[i][j] > temp)
                {
                    matrizEntrada[i][j] = temp;
                    matrizRespuesta[i][j] = k+1;
                }
            }
        }
        
    imprimirMatriz(matrizEntrada);  
    pasarResultado(matrizEntrada);
}

void infinitos()
{
    for(int i = 0; i < nodos; i++)
    {
        for(int j = 0; j < nodos; j++)
        {
            if(matrizEntrada[i][j] == INF)
            {
                matrizRespuesta[i][j] = INF;
            }
        }
    }
}

//Resuelve Floyd paso por paso
void siguiente_clicked(){
    char value[40];

    if(k == 0)
    {
        matrizEntrada = inicializarMatriz(nodos, INF);
        matrizRespuesta = inicializarMatriz(nodos, 0);
        anhadirInput(matrizEntrada);
        gtk_button_set_label(GTK_BUTTON(siguiente), "Siguiente");        

    }
    if(k < nodos-1)
    {
        floyd(nodos);
        k = k+1;
        sprintf(value, "Resultado D(%i)", k );
        digraph(0,NULL);
        gtk_label_set_text(GTK_LABEL(resultado), value);        
        
    }
    else
    {
        floyd(nodos);
        sprintf(value, "Resultado D(%i)", k+1);
        gtk_label_set_text(GTK_LABEL(resultado), value);
        infinitos();
        gtk_widget_set_sensitive(buttonRutas, 1);
        gtk_widget_set_sensitive (siguiente,0);
        digraph(0, NULL);
    }
    
    
  
    
}


//Salva el nombre de los nodos.

void cambiarNombre_clicked()
{
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

void buttonRutas_clicked()
{
    

    for(int j = 1; j<nodos+1; j++)
    {
        GtkWidget *z;
        z = gtk_grid_get_child_at(GTK_GRID(gridEntrada),0,j);
        const gchar *pointer;
        pointer = gtk_entry_get_text(GTK_ENTRY(z));
        nombres[j-1] = pointer[0];
        gtk_combo_box_text_insert_text (GTK_COMBO_BOX_TEXT(comboBoxText_Partida), j-1, pointer);
        gtk_combo_box_text_insert_text (GTK_COMBO_BOX_TEXT(comboBoxText_Destino), j-1, pointer);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBoxText_Partida), 0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBoxText_Destino), 0);
    imprimirMatriz(matrizRespuesta);
    gtk_widget_show(window_aux);
    
}

void rutas_cerrar()
{
    gtk_widget_hide(window_aux);
}

void encontrarRutaAux(int p, int d, char str[80], char gph[160])
{
    char c[2];
    int temp = 0;
    temp = matrizRespuesta[p][d];
    //pointer = g_strconcat(pointer, "->", nombres[d], NULL);
    
    if(temp != 0)
    {
        int ruta = 0;
        ruta = matrizRespuesta[p][temp-1];
        if(ruta != 0)
        {
            sprintf(c, "%c", nombres[ruta-1]);
            strcat(str, "->");
            strcat(str, c);
            strcat(gph, " -> ");
            strcat(gph, c);
            encontrarRutaAux(ruta-1, d, str, gph);
        }
        else
        {
            sprintf(c, "%c", nombres[temp-1]);
            strcat(str, "->");
            strcat(str, c);
            strcat(gph, " -> ");
            strcat(gph, c);
            encontrarRutaAux(temp-1, d, str, gph);
        }
        
        
    }
    else
    {

        sprintf(c, "%c", nombres[d]);
        strcat(str, "->");
        strcat(str, c);
        strcat(gph, " -> ");
        strcat(gph, c);
        strcat(gph, "[color=red, penwidth=3.0];\n");
        //g_print(gph);
        digraph(1, gph);
        gtk_label_set_text(GTK_LABEL(rutas_resultado), str);
        g_print("%s",str);
    }
}

void encontrarRuta(int p, int d)
{
    if(matrizRespuesta[p][d] == INF)
    {
        gtk_label_set_text(GTK_LABEL(rutas_resultado), "Resultado: No hay rutas que conecten esos dos nodos");
    }
    else
        if(p == d)
        {
         gtk_label_set_text(GTK_LABEL(rutas_resultado), "Resultado: Ni se mueva");
        }
         else
         {

            char str[80];
            char gph[160];
            memset(&gph[0], 0, sizeof(gph));  
         //   g_print("aca\n");
    	//	g_print(gph);          
            strcpy(str, "Resultado: ");
            //strcpy(gph, "digraph G {\n");
            char c[2];
            sprintf(c, "%c", nombres[p]);
            strcat(str, c);
            strcat(gph, "\t");
            strcat(gph, c);
            //g_print("%s", str);

            encontrarRutaAux(p,d, str, gph);
         }
            
}



void rutas_calcular()
{
    int i, j;
    i = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBoxText_Partida));
    j = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxText_Destino));
    g_print("%d-%d", i, j);
    encontrarRuta(i,j);
}

void buttonTablasP_clicked()
{

    gtk_widget_show(windowTablas);
}

void cerrarTablasP_clicked()
{
    gtk_widget_hide(windowTablas);
}

void btnCerrarGrafo_clicked_cb()
{
    gtk_widget_hide(windowGrafo);
}

void rutas_key_release_event_cb()
{
	g_print("hola");
	matrizEntrada = inicializarMatriz(nodos, INF);
    matrizRespuesta = inicializarMatriz(nodos, 0);
    anhadirInput(matrizEntrada);
	digraph(0,NULL);

	//matrizEntrada = inicializarMatriz(nodos, INF);
	//anhadirInput(matrizEntrada);

}

static gboolean
_label_update(gpointer data)
{


    system("dot -Tpng grafo.dot -o grafo.png");
    gtk_image_set_from_file (image, "grafo.png");
    return continue_timer;

}

static void
_start_timer (GtkWidget *button, gpointer data)
{
    (void)button;/*Avoid compiler warnings*/
    GtkWidget *label = data;
    if(!start_timer)
    {
        g_timeout_add_seconds(1, _label_update, label);
        start_timer = TRUE;
        continue_timer = TRUE;
    }
}


int main(int argc, char *argv[])
{

    GtkBuilder      *builder; 
    

 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/rutas_optimas.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "rutas"));
    buttonRutas = GTK_WIDGET(gtk_builder_get_object(builder, "buttonRutas"));
    gtk_widget_set_sensitive(buttonRutas, 0);
    window_aux = GTK_WIDGET(gtk_builder_get_object(builder, "window_aux"));
    gtk_builder_connect_signals(builder, NULL);
    windowTablas = GTK_WIDGET(gtk_builder_get_object(builder, "windowTablas"));

    //Crea la ventana para el grafo
    windowGrafo = GTK_WIDGET(gtk_builder_get_object(builder, "windowGrafo"));
    gtk_widget_show(windowGrafo);
	image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

    scroll = GTK_WIDGET(gtk_builder_get_object(builder, "scroll"));
    comboBoxText_Partida = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxText_Partida"));
    comboBoxText_Destino = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxText_Destino"));
    rutas_resultado = GTK_WIDGET(gtk_builder_get_object(builder, "rutas_resultado"));
    siguiente = GTK_WIDGET(gtk_builder_get_object(builder, "siguiente"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    mEntrada = GTK_WIDGET(gtk_builder_get_object(builder, "mEntrada"));
    mRespuesta = GTK_WIDGET(gtk_builder_get_object(builder, "mRespuesta"));
    mTablasP = GTK_WIDGET(gtk_builder_get_object(builder, "mTablasP"));
    resultado = GTK_WIDGET(gtk_builder_get_object(builder, "resultado"));

    
    limpiar();
    nombres = calloc(nodos,sizeof(const char));
    digraphVacia();




    g_object_unref(builder);    
    gtk_widget_show(window); 

    g_timeout_add(250, _label_update, image);
    continue_timer = TRUE;
    start_timer = TRUE;


    gtk_main();


    
 
    return 0;
} 
 


