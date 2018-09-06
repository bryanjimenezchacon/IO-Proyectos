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
GdkColor color1;

GtkWidget *calcular,*folder, *filenameEntry, *guardar, *tabla_input, *tabla_solucion, *table, *SalirDelPrograma, *grid1, *grid2, *gridt, *cantObj, *capacidad, *result, *resultadoFinal, *label, *box, *objetos, *maximizar;
char *strs[50]= {"Objeto \n","Valor\n","Costo\n","#\n"};
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
    folder = GTK_WIDGET(gtk_builder_get_object(builder, "folder"));
    filenameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "filename"));

    calcular = GTK_WIDGET(gtk_builder_get_object(builder, "calcular"));
    cantObj = GTK_WIDGET(gtk_builder_get_object(builder, "cantObj"));

    guardar = GTK_WIDGET(gtk_builder_get_object(builder, "guardar_SD"));
    SalirDelPrograma = GTK_WIDGET(gtk_builder_get_object(builder, "SalirDelPrograma"));
    result = GTK_WIDGET(gtk_builder_get_object(builder, "result"));
    resultadoFinal = GTK_WIDGET(gtk_builder_get_object(builder, "resultadoFinal"));
    maximizar = GTK_WIDGET(gtk_builder_get_object(builder, "maximizar"));
    tabla_solucion = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_solucion"));
    tabla_input = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_input"));
   
    capacidad = GTK_WIDGET(gtk_builder_get_object(builder, "capacidad"));
    objetos = GTK_WIDGET(gtk_builder_get_object(builder, "objetos"));
   
    gtk_widget_set_tooltip_text(folder, "Seleccionar un directorio");
    gtk_widget_set_tooltip_text(filenameEntry, "Nombre del archivo a guardar");
    gtk_widget_set_tooltip_text(guardar, "Guarda los datos en un archivo");
    gtk_widget_set_tooltip_text(SalirDelPrograma, "Cierra el programa");

    gdk_color_parse ("#d6d6d6", &color1);

    gtk_widget_modify_bg ( GTK_WIDGET(window_SD), GTK_STATE_NORMAL, &color1);

    gtk_label_set_text(GTK_LABEL(result), "Utilice \"*\" para indicar cantidad infinito.");
    g_object_unref(builder);
    gtk_widget_set_sensitive (calcular,0);
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

void SignalSalir()
{
    gtk_widget_destroy(GTK_WIDGET(window_SD));
}

void SignalAbrir()
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new ("Abrir archivo", GTK_WINDOW(window_SD),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    gtk_widget_show_all(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
    {
        readFile(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    }
    gtk_widget_destroy(dialog);
}

void SignalSalvar()
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new ("Salvar archivo", GTK_WINDOW(window_SD),GTK_FILE_CHOOSER_ACTION_SAVE,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    gtk_widget_show_all(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
    {
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        writeFile(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    }
    gtk_widget_destroy(dialog);

}

int on_calcular_clicked(){
    deleteTablesGrid(tabla_solucion);
    gtk_label_set_text(GTK_LABEL(resultadoFinal), "");
    gtk_label_set_text(GTK_LABEL(result), "");

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
    strcpy(val,"Z = ");
    char v[300000];
    for(int i=1;i<=cantidadObjetos;i++){ 
        for(int j=2;j<5;j++){
            
                const gchar *cant_nodos;
                cant_nodos = gtk_entry_get_text(gtk_grid_get_child_at (gridt,j,i));
                int valor = atoi(cant_nodos);
                if(cant_nodos[0]== '*'){
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
                    sprintf(v,"%d*x%d\n\nRestricciones :", tabla[i][j], i+1);
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
    gtk_label_set_text(GTK_LABEL(maximizar), val);

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
                char *str = g_strdup_printf ("<span color=\"white\">"                              
                            "%s"
                             "</span>",
                             val);
                gtk_label_set_markup(GTK_LABEL (label), str);
                gtk_widget_set_size_request(label, 580/(cantidadObjetos + 1), 580/(cantidadObjetos + 1));
                box = gtk_box_new(0, 0);
                gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                const GdkRGBA *color;
                    
                gdk_color_parse( "#534C8D", &color );
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
                    char *str = g_strdup_printf ("<span color=\"white\">"                              
                            "%s"
                             "</span>",
                             val);
                gtk_label_set_markup(GTK_LABEL (label), str);
                    gtk_widget_set_size_request(label, 580/(cantidadObjetos + 1), 580/(cantidadObjetos + 1));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    gdk_color_parse( "#534C8D", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j, i, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);
                }
            
                else {
                    char v[100];
                 
                    sprintf(v,"%d", tablaResultado[i-1][j-1]);
                    label = gtk_label_new (v);
                    char *str = g_strdup_printf ("<span color=\"white\">"                              
                            "%s"
                             "</span>",
                             v);
                gtk_label_set_markup(GTK_LABEL (label), str);
                    gtk_widget_set_size_request(label, 580/(cantidadObjetos + 1), 580/(cantidadObjetos+ 1));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    if(tablaResultadoAux[i-1][j-1]>=1){ 
                    gdk_color_parse( "#51A54D", &color );}
                    else{
                        gdk_color_parse( "#B45474", &color );
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
            if(cant_nodos[0]=='*'){
                fprintf(file, "%s\n", cant_nodos);
            }else{
                int valor = atoi(cant_nodos);
                fprintf(file, "%i\n", valor);
            }
        }
    }

    

    fclose(file);
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
        sprintf(v,"%s: %i copias\n", strsAux[j], numberOfCopies);
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



void readFile(char* filename)
{

    FILE *file;
    file = fopen(filename, "r");
    deleteTablesGrid(tabla_input); 
    char array[100];
    fgets(array, sizeof(array), file);
    strip(array);
    cantidadObjetos = atoi(array);
    gtk_range_set_value(GTK_SCALE(objetos), cantidadObjetos);
    fgets(array, sizeof(array), file);
    strip(array);
    capacidadMochila = atoi(array);
    gtk_range_set_value(GTK_SCALE(capacidad), capacidadMochila);
    
    
    g_print("%d", capacidadMochila);
    

    if(capacidadMochila == 0 || cantidadObjetos == 0)
    {
        gtk_widget_set_sensitive (calcular,0);
    }
    else
    {
        gtk_widget_set_sensitive (calcular,1);
    }


    gridt = gtk_grid_new ();
    gtk_grid_set_row_spacing (gridt, 5);
    gtk_grid_set_column_spacing (gridt, 5);
    char v[5];

    for (int i = 0; i < cantidadObjetos+1; i++)
    {
        
        for(int j = 0; j < 5; j++)
        {               
            if(i==0)
            { 
                GtkWidget *labelf = gtk_label_new (strs[j-1]); 
                gtk_grid_attach(GTK_GRID(gridt), labelf, j, 0, 1, 1);
                gtk_widget_show (labelf);
            }     
            if(j==1&&i!=0)
            {              
                sprintf(v,"%s",strsAux[i-1]);
                GtkWidget *labelf = gtk_label_new (v);     
                gtk_grid_attach(GTK_GRID(gridt), labelf, 1, i, 1, 1);
                gtk_widget_show (labelf);
            }
            if(j>1&&i!=0)
            {
                GtkWidget *entry = gtk_entry_new();
                gtk_entry_set_width_chars(entry,3);
                fgets(array, sizeof(array), file);
                strip(array); 
                gtk_entry_set_text(GTK_ENTRY(entry), array);
                gtk_grid_attach(GTK_GRID(gridt), entry, j, i, 1, 1);
                gtk_widget_show (entry);
            }
        }
    }
    gtk_container_add (GTK_CONTAINER (tabla_input), gridt);
    gtk_widget_show (gridt);
    fclose(file);
}    

void actualizarInput()
{
    deleteTablesGrid(tabla_input);    
    capacidadMochila = (int)gtk_range_get_value(GTK_RANGE(capacidad));
    cantidadObjetos = (int)gtk_range_get_value(GTK_RANGE(objetos));

    if(capacidadMochila == 0 || cantidadObjetos == 0)
    {
        gtk_widget_set_sensitive (calcular,0);
    }
    else
    {
        gtk_widget_set_sensitive (calcular,1);
    }


    gridt = gtk_grid_new ();
    gtk_grid_set_row_spacing (gridt, 5);
    gtk_grid_set_column_spacing (gridt, 5);
    char v[5];

    for (int i = 0; i < cantidadObjetos+1; i++)
    {
        
        for(int j = 0; j < 5; j++)
        {               
            if(i==0)
            { 
                GtkWidget *labelf = gtk_label_new (strs[j-1]); 
                gtk_grid_attach(GTK_GRID(gridt), labelf, j, 0, 1, 1);
                gtk_widget_show (labelf);
            }     
            if(j==1&&i!=0)
            {              
                sprintf(v,"%s",strsAux[i-1]);
                GtkWidget *labelf = gtk_label_new (v);     
                gtk_grid_attach(GTK_GRID(gridt), labelf, 1, i, 1, 1);
                gtk_widget_show (labelf);
            }
            if(j>1&&i!=0)
            {
                GtkWidget *entry = gtk_entry_new();
                gtk_entry_set_width_chars(entry,3);
                gtk_entry_set_text(GTK_ENTRY(entry), "0");
                gtk_grid_attach(GTK_GRID(gridt), entry, j, i, 1, 1);
                gtk_widget_show (entry);
            }
        }
    }
    gtk_container_add (GTK_CONTAINER (tabla_input), gridt);
    gtk_widget_show (gridt);
}

void on_objetos_value_changed()
{

    actualizarInput();
     
}

void on_capacidad_value_changed()
{


    actualizarInput();
    
}




