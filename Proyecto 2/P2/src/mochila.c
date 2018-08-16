/************************************************************************
# 
# Instituto Tecnológico de Costa Rica
# Investigación de Operaciones Gr 40
#
#
# Proyecto 2.Problema de la mochila
#
# Profesor: Dr.Francisco J.Torres Rojas
#
# Bryan Steve Jiménez Chacón
# Patrick Maynard Gamboa
# Dario Monestel Corella
# 
# II Semestre 2018
# ************************************************************************/

#include <glib.h>
#include <gtk/gtk.h>
#include "lib/matrix.c"

 
GtkBuilder  *builder; 
GtkWidget  *window_SD;


GtkWidget * btn_cargar_SD;
GtkWidget *entry_cargar_SD;
GtkWidget *btn_calcular_SD;
GtkWidget *folder;
GtkWidget *filenameEntry;
GtkWidget *guardar;
GtkWidget *tabla_input;
GtkWidget *tabla_solucion;

GtkWidget *table;
GtkWidget *SalirDelPrograma;


GtkWidget *grid1;
GtkWidget *grid2;
GtkWidget *gridt;

GtkWidget *cantObj;
GtkWidget *capacidad;

GtkWidget *result;
GtkWidget *resultadoFinal;


GtkWidget *label;
GtkWidget *box;
char *strs[50]= {"Objeto ","Valor","Costo","Cantidad"};
char *strsAux[20]= {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"};




int ** tabla;
int ** tablaResultado;
int ** tablaResultadoAux;
int capacidadMochila=-1;
int cantidadObjetos = 0;
int array[2];



char val[300000];

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/Mochila.glade", NULL);
 
    window_SD = GTK_WIDGET(gtk_builder_get_object(builder, "window_SD"));

    gtk_builder_connect_signals(builder, NULL);   
    entry_cargar_SD = GTK_WIDGET(gtk_builder_get_object(builder, "entry_cargar_SD"));
    folder = GTK_WIDGET(gtk_builder_get_object(builder, "folder"));
    filenameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "filename"));

    btn_calcular_SD = GTK_WIDGET(gtk_builder_get_object(builder, "btn_calcular_SD"));
    cantObj = GTK_WIDGET(gtk_builder_get_object(builder, "cantObj"));

    guardar = GTK_WIDGET(gtk_builder_get_object(builder, "guardar_SD"));
    btn_cargar_SD = GTK_WIDGET(gtk_builder_get_object(builder, "btn_cargar_SD"));
    SalirDelPrograma = GTK_WIDGET(gtk_builder_get_object(builder, "SalirDelPrograma"));
    result = GTK_WIDGET(gtk_builder_get_object(builder, "result"));
    resultadoFinal = GTK_WIDGET(gtk_builder_get_object(builder, "resultadoFinal"));
    tabla_solucion = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_solucion"));
    tabla_input = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_input"));
   
    capacidad = GTK_WIDGET(gtk_builder_get_object(builder, "capacidad"));
   
    gtk_widget_set_tooltip_text(entry_cargar_SD, "Seleccionar un archivo");
    gtk_widget_set_tooltip_text(btn_calcular_SD, "Calcula la tabla con las probabilidades de A y B");
    gtk_widget_set_tooltip_text(folder, "Seleccionar un directorio");
    gtk_widget_set_tooltip_text(filenameEntry, "Nombre del archivo a guardar");
    gtk_widget_set_tooltip_text(guardar, "Guarda los datos en un archivo");
    gtk_widget_set_tooltip_text(btn_cargar_SD, "Carga el archivo seleccionado");
    gtk_widget_set_tooltip_text(SalirDelPrograma, "Cierra el programa");


    gtk_label_set_text(GTK_LABEL(result), "Utilice \"-\" para indicar cantidad infinito.");
    g_object_unref(builder);
    gtk_widget_show(window_SD);                         
                              
    gtk_main();
    return 0;
} 
 



void deleteTablesGrid(GtkWidget *widget)
{
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(widget));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);

}

int on_btn_calcular_clicked(){
    deleteTablesGrid(tabla_solucion);
    gtk_label_set_text(GTK_LABEL(resultadoFinal), "");
    gtk_label_set_text(GTK_LABEL(result), "");
	/*
    tabla = createFloatMatrix(cantidadObjetos, 3);
    tablaCantidades = createFloatMatrix(capacidadMochila+1, cantidadObjetos);
    tablaColumnaAnterior = createFloatMatrix(capacidadMochila+1, 1);
    cantidadCombinaciones = createFloatMatrix(cantidadObjetos, 1);
    tablaResultado = createFloatMatrix(capacidadMochila+1, cantidadObjetos);*/

    if(cantidadObjetos==0){
        gtk_label_set_text(GTK_LABEL(result), "Debe de llenar la información primero.");
        return 0;
    }

    if(capacidadMochila==-1){
        gtk_label_set_text(GTK_LABEL(result), "Tiene que poner una capacidad primero.");
        return 0;
    }
    tabla = createMatrix(cantidadObjetos, 3);
    tablaResultado = createMatrix(capacidadMochila+1, cantidadObjetos);
    tablaResultadoAux = createMatrix(capacidadMochila+1, cantidadObjetos);
    strcpy(val,"Maximizar\n\nZ = ");
    char v[300000];
    for(int i=1;i<=cantidadObjetos;i++){ 
        for(int j=2;j<5;j++){
            
                const gchar *cant_nodos;
                cant_nodos = gtk_entry_get_text(gtk_grid_get_child_at (gridt,j,i));
                int valor = atoi(cant_nodos);
                if(cant_nodos[0]== '-'){
                    tabla[i-1][j-2] = -1;
                }
                else if(valor==0){
                    gtk_label_set_text(GTK_LABEL(result), "Los valores de la tabla no pueden tener letras y tienen que ser mayor que 0.");
                    return 0;
                }
                else if(valor < 0){
                        gtk_label_set_text(GTK_LABEL(result), "Los valores de la tabla tienen que ser mayor o igual que 0");
                        return 0;
                    }
                else{
                        tabla[i-1][j-2] = valor;
                     }
            
        }
    }
    for(int j = 0; j < 2; j++){
        for(int i = 0; i < cantidadObjetos;i++){
            if(j == 0){
                if(i+1 != cantidadObjetos){
                    sprintf(v,"%d*x%d + ", tabla[i][j], i+1);
                    strcat(val,v);
                }else{
                    sprintf(v,"%d*x%d\n\nSujeto a:\n\n", tabla[i][j], i+1);
                    strcat(val,v);
                }
            }
            else if(j == 1){
                if(i+1 != cantidadObjetos){
                    sprintf(v,"%d*x%d + ", tabla[i][j], i+1);
                    strcat(val,v);
                }else{
                    sprintf(v,"%d*x%d <=", tabla[i][j], i+1);
                    strcat(val,v);
                }
            }
        }
    }
    sprintf(v,"%d", capacidadMochila);
    strcat(val,v);
    gtk_label_set_text(GTK_LABEL(result), val);

    knapsack();
    CrearTabla();
    obtenerResultado();
}

void on_SalirDelPrograma_clicked()
{
    gtk_widget_destroy(window_SD);
}

int knapsack(){

    int q;
    int valor;
    
    for (int j = 0; j < cantidadObjetos; j++){
        for(int i = 0; i <= capacidadMochila; i++){
            q = 0;
            while (q * tabla[j][1] <= i){
                
                valor = q * tabla[j][0];
                if (j > 0){
                    valor += tablaResultado[i - q * tabla[j][1]][j - 1];
                }
                if (valor > tablaResultado[i][j]){
                    tablaResultadoAux[i][j] = q;                     
                    tablaResultado[i][j] = valor;                    
                    
                }
                q++;
                if (q > tabla[j][2] && tabla[j][2] != -1){
                    break;
                }
            }
        }
    }

}

void CrearTabla(){
    grid2 = gtk_grid_new ();
    gtk_grid_set_row_spacing (grid2, 1);
    gtk_grid_set_column_spacing (grid2, 1);

    for (int i = 0; i <= capacidadMochila+1; i++)
    {
        for(int j = 0; j <= cantidadObjetos; j++)
        {   

            if(i==0){
                if(j!=cantidadObjetos){
                char val[30];
                sprintf(val,"%s", strsAux[j]);
                label = gtk_label_new (val);
                gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos + 2));
                box = gtk_box_new(0, 0);
                gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                const GdkRGBA *color;
                    
                gdk_color_parse( "#467DD9", &color );
                gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                gtk_grid_attach(GTK_GRID(grid2), box, j+1, i, 1, 1);

                gtk_widget_show (label);
                gtk_widget_show (box); } 
            }
            else{
                if(j==0){
                    char val[30];
                    sprintf(val,"%d", i-1);

                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos + 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    gdk_color_parse( "#AFC6EE", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j, i, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);
                }
            
                else {
                    char v[100];
                 
                    sprintf(v,"%d", tablaResultado[i-1][j-1]);
                    label = gtk_label_new (v);
                    gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos+ 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    if(tablaResultadoAux[i-1][j-1]>=1){ 
                    gdk_color_parse( "#00FF00", &color );}
                    else{
                        gdk_color_parse( "#FF0000", &color );
                    }
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j, i, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);  
                }
      
            }
        }
    }

    gtk_container_add (GTK_CONTAINER (tabla_solucion), grid2);
    gtk_widget_show (grid2); 
}


int on_guardar_SD_clicked ()
{
    char * filename[250];
    char* name = gtk_entry_get_text (filenameEntry);

    if(strlen(name)==0){
        gtk_label_set_text(GTK_LABEL(result), "Escriba el nombre del archivo.");
        return 0;
    }

    char* folderfile = gtk_file_chooser_get_filename(folder);
    if(folderfile==NULL){
        gtk_label_set_text(GTK_LABEL(result), "Selecione un folder.");
        return 0;
    }

    sprintf(filename,"%s/%s", folderfile, name);
    writeFile(filename);
    gtk_entry_set_text (filenameEntry, "");
    gtk_label_set_text(GTK_LABEL(result), "Se guardó exitosamente.");

}

void writeFile(char* filename)
{

    FILE *file;
    file = fopen(filename, "w");
    
    fprintf(file, "%i\n", cantidadObjetos);
    fprintf(file, "%i\n", capacidadMochila);
    const gchar *cant_nodos;
    for(int i=1;i<=cantidadObjetos;i++){ 
        for(int j=2;j<5;j++){
            const gchar *cant_nodos;
            cant_nodos = gtk_entry_get_text(gtk_grid_get_child_at (gridt,j,i));
            if(cant_nodos[0]=='-'){
                fprintf(file, "%s\n", cant_nodos);
            }else{
                int valor = atoi(cant_nodos);
                fprintf(file, "%i\n", valor);
            }
        }
    }

    

    fclose(file);
}

int on_btn_cargar_SD_clicked(){
    const gchar *filename;
    filename = gtk_file_chooser_get_filename (entry_cargar_SD);
    if(filename==NULL){
        gtk_label_set_text(GTK_LABEL(result), "Selecione un archivo.");
        return 0;
    }
    readFile(filename);
}

void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
        if(*s != '\t' && *s != '\n') {
            *p2++ = *s++;
        } else {
            ++s;
        }
    }
    *p2 = '\0';
}

void obtenerResultado ()
{
    int j = cantidadObjetos-1;
    int i = capacidadMochila;
    strcpy(val,"");
    int numberOfCopies;
    char v[300000];
    char vAux[3000];
    char vAux2[3000];
    strcpy(vAux,"");
    strcpy(vAux2,"Resultado: ");
    while (j >= 0)
    {
        
 
        numberOfCopies = tablaResultadoAux[i][j];
        sprintf(v,"Objeto %s llevar: %i copias\n", strsAux[j], numberOfCopies);
        strcat(val,v);
        if(numberOfCopies > 0){
            if(j-1<0){
                sprintf(vAux,"%d*%s",numberOfCopies,strsAux[j]);
                strcat(vAux2,vAux);
            }
            else{
                sprintf(vAux,"%d*%s, ",numberOfCopies,strsAux[j]);
                strcat(vAux2,vAux);
            }
        }
        i = i - numberOfCopies * tabla[j][1];
        j--;
    
    }
    strcat(val,"\n");
    strcat(val,vAux2);
    gtk_label_set_text(GTK_LABEL(resultadoFinal), val);

}

void readFile(char* filename)
{    

    FILE *file;
    file = fopen(filename, "r");
    char array[10];
    fgets(array, sizeof(array), file);
    strip(array);
    //fscanf(file, "%i", &nnodos);
    cantidadObjetos = atoi(array);
    gtk_entry_set_text(cantObj,array);

    fgets(array, sizeof(array), file);
    strip(array);
    //fscanf(file, "%i", &nnodos);
    capacidadMochila = atoi(array);
    gtk_entry_set_text(capacidad,array);
    on_acept_clicked();

    for(int i=1;i<=cantidadObjetos;i++){ 
        for(int j=2;j<5;j++){        

            fgets(array, sizeof(array), file);
            strip(array); //Quita espacios null
            gtk_entry_set_text(gtk_grid_get_child_at(gridt,j,i),array);
        }
    }

    fclose(file);
    
 
}

float stof(char* s){
  float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1; 
      continue;
    };
    int d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };
  };
  return rez * fact;
};



int on_acept_clicked(){
    
    deleteTablesGrid(tabla_input);    
    gtk_label_set_text(GTK_LABEL(result), "Utilice \"-\" para indicar cantidad infinito.");
    const gchar *pln;
    
    pln = gtk_entry_get_text(capacidad);
    capacidadMochila = atoi(pln);

    if(strlen(pln)==0){
        gtk_label_set_text(GTK_LABEL(result), "Debe de especificar una capacidad.");
        return 0;
    }


    pln = gtk_entry_get_text(cantObj);
    cantidadObjetos = atoi(pln);

    if(strlen(pln)==0){
        gtk_label_set_text(GTK_LABEL(result), "Debe de especificar una cantidad de objetos.");
        return 0;
    }

    if(capacidadMochila  < 0||capacidadMochila  > 100){
        gtk_label_set_text(GTK_LABEL(result), "La capacidad tiene que ser mayor o igual que 0 y menor que 100.");
        return 0;
    }

    if(cantidadObjetos <= 0||cantidadObjetos > 20){
        gtk_label_set_text(GTK_LABEL(result), "La capacidad tiene que ser mayor que 0 y menor que 20");
        return 0;
    }

    gridt = gtk_grid_new ();
    gtk_grid_set_row_spacing (gridt, 5);
    gtk_grid_set_column_spacing (gridt, 5);
    char v[5];

    for (int i = 0; i < cantidadObjetos+1; i++)
    {
        
        for(int j = 0; j < 5; j++)
        {               
            if(i==0){ 
                GtkWidget *labelf = gtk_label_new (strs[j-1]);  
                gtk_grid_attach(GTK_GRID(gridt), labelf, j, 0, 1, 1);
                gtk_widget_show (labelf);}     
            if(j==1&&i!=0){              
                sprintf(v,"%s",strsAux[i-1]);
                GtkWidget *labelf = gtk_label_new (v);     
                gtk_grid_attach(GTK_GRID(gridt), labelf, 1, i, 1, 1);
                gtk_widget_show (labelf);}
            if(j>1&&i!=0){
            GtkWidget *entry = gtk_entry_new();
            gtk_entry_set_width_chars(entry,3);
            gtk_grid_attach(GTK_GRID(gridt), entry, j, i, 1, 1);
            gtk_widget_show (entry);}
        }
    }
    gtk_container_add (GTK_CONTAINER (tabla_input), gridt);
    gtk_widget_show (gridt);

   
}


