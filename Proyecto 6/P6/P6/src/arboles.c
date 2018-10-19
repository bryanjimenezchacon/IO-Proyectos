/************************************************************************
 
 Instituto Tecnológico de Costa Rica
 Investigación de Operaciones
 II Semestre 2017

 Proyecto 0.Menú de Programas de Programación Dinámica

 Profesor: Dr.Francisco J.Torres Rojas

 Melissa Molina Corrales
 Edwin Cen Xu
 Willian Espinoza
 Cristian León

 ************************************************************************/

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
GtkWidget *tabla_R;

GtkWidget *table;
GtkWidget *SalirDelPrograma;


GtkWidget *grid1;
GtkWidget *grid2;
GtkWidget *gridt;

GtkWidget *cantObj;
GtkWidget *capacidad;
GtkWidget *orden;

GtkWidget *result;
GtkWidget *resultadoFinal;


GtkWidget *label;
GtkWidget *box;
char *strs[50]= {"Llave","Valor"};
char *strsAux[2000]= {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"};




float ** tabla;
float ** tablaResultado;
int ** tablaResultadoAux;
float ** promedios;
int capacidadMochila=-1;
int cantidadObjetos = 0;
int array[20];



char val[300000];

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/Arboles.glade", NULL);
 
    window_SD = GTK_WIDGET(gtk_builder_get_object(builder, "window_SD"));

    gtk_builder_connect_signals(builder, NULL);   
    entry_cargar_SD = GTK_WIDGET(gtk_builder_get_object(builder, "entry_cargar_SD"));
    folder = GTK_WIDGET(gtk_builder_get_object(builder, "folder"));
    filenameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "filename"));

    btn_calcular_SD = GTK_WIDGET(gtk_builder_get_object(builder, "btn_calcular_SD"));
    cantObj = GTK_WIDGET(gtk_builder_get_object(builder, "cantObj"));
    orden = GTK_WIDGET(gtk_builder_get_object(builder, "orden"));

    guardar = GTK_WIDGET(gtk_builder_get_object(builder, "guardar_SD"));
    btn_cargar_SD = GTK_WIDGET(gtk_builder_get_object(builder, "btn_cargar_SD"));
    SalirDelPrograma = GTK_WIDGET(gtk_builder_get_object(builder, "SalirDelPrograma"));
    result = GTK_WIDGET(gtk_builder_get_object(builder, "result"));
    resultadoFinal = GTK_WIDGET(gtk_builder_get_object(builder, "resultadoFinal"));
    tabla_solucion = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_solucion"));
    tabla_R = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_R"));
    tabla_input = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_input"));
   
    capacidad = GTK_WIDGET(gtk_builder_get_object(builder, "capacidad"));
   
    gtk_widget_set_tooltip_text(entry_cargar_SD, "Seleccionar un archivo");
    gtk_widget_set_tooltip_text(btn_calcular_SD, "Calcula la tabla con las probabilidades de A y B");
    gtk_widget_set_tooltip_text(folder, "Seleccionar un directorio");
    gtk_widget_set_tooltip_text(filenameEntry, "Nombre del archivo a guardar");
    gtk_widget_set_tooltip_text(guardar, "Guarda los datos en un archivo");
    gtk_widget_set_tooltip_text(btn_cargar_SD, "Carga el archivo seleccionado");
    gtk_widget_set_tooltip_text(SalirDelPrograma, "Cierra el programa");



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

void sortCopyPasta(){
    char temp[20];
    float tempNum;
    for (int i = 0; i < cantidadObjetos - 1 ; i++)
    {
        for (int j = i + 1; j < cantidadObjetos; j++)
        {
            if (strcmp(strsAux[i], strsAux[j]) > 0)
            {
                strcpy(temp, strsAux[i]);
                strcpy(strsAux[i], strsAux[j]);
                strcpy(strsAux[j], temp);
                tempNum = tabla[i][1];
                tabla[i][1] = tabla[j][1];
                tabla[j][1] = tempNum;
            }
        }
    }
}

int on_btn_calcular_clicked(){
    deleteTablesGrid(tabla_solucion);
    deleteTablesGrid(tabla_R);
    gtk_label_set_text(GTK_LABEL(resultadoFinal), "");
    gtk_label_set_text(GTK_LABEL(result), "");
    gtk_label_set_text(GTK_LABEL(orden), "");
	/*
    tabla = createFloatMatrix(cantidadObjetos, 3);
    tablaCantidades = createFloatMatrix(capacidadMochila+1, cantidadObjetos);
    tablaColumnaAnterior = createFloatMatrix(capacidadMochila+1, 1);
    cantidadCombinaciones = createFloatMatrix(cantidadObjetos, 1);
    tablaResultado = createFloatMatrix(capacidadMochila+1, cantidadObjetos);*/

    tabla = createFloatMatrix(cantidadObjetos, 2);
    promedios = createFloatMatrix(cantidadObjetos,1);
    tablaResultado = createFloatMatrix(cantidadObjetos+2, cantidadObjetos+1);
    tablaResultadoAux = createMatrix(cantidadObjetos+2,cantidadObjetos+1);

    for(int i=1;i<=cantidadObjetos;i++){ 
        for(int j=0;j<2;j++){
                if(j==1){
                    const gchar *cant_nodos;
                    cant_nodos = gtk_entry_get_text(gtk_grid_get_child_at (gridt,j,i));
                    float valor;
                    sscanf(cant_nodos, "%f", &valor);
                    if(strlen(cant_nodos)==0){
                    	gtk_label_set_text(GTK_LABEL(result), "Debe llenar todos los campos solicitados.");
                            return 0;
                    }
                    if(strlen(cant_nodos)>50){
                    	gtk_label_set_text(GTK_LABEL(result), "La llave debe de tener menos de 50 letras.");
                            return 0;
                    }
                    for(int i = 0 ; i <strlen(cant_nodos);i++){
                        if(cant_nodos[i]==','){
                            continue;
                        }
                        if(isdigit(cant_nodos[i])==FALSE){
                            gtk_label_set_text(GTK_LABEL(result), "No puede haber letras en el valor y utilice \",\" para decimales.");
                            return 0;
                        }
                    }
                    tabla[i-1][j] = valor;
                }
                else {
                    const gchar *cant_nodos;
                    cant_nodos = gtk_entry_get_text(gtk_grid_get_child_at (gridt,j,i));
                    strsAux[i-1]= cant_nodos;
                }

        }

    }
    sortCopyPasta();



    float r = 0.0;
    for(int t = 0;t <cantidadObjetos;t++){
        r+=tabla[t][1];
    }

    for(int i=0;i<cantidadObjetos;i++){
        promedios[i][0]= tabla[i][1]/r;
    }

    char v[3000000];
    strcpy(v,"Orden: \n\n");
    for(int i = 0; i < cantidadObjetos;i++){
        char val[10];
        sprintf(val,"%d: ",i+1);
        strcat(v,val);
        strcat(v,strsAux[i]);
        strcat(v," - ");
        sprintf(val,"%f\n",promedios[i][0]);
        strcat(v,val);
    }
    gtk_label_set_text(GTK_LABEL(orden), v);

    for(int i = 1;i<cantidadObjetos+1;i++){
        for(int j = 1; j< cantidadObjetos+1;j++){
            if(i == j){
                tablaResultado[i][j] += promedios[i-1][0];
                tablaResultadoAux[i][j] = i;
            }
            //printf("%f  ",tablaResultado[i][j] );
        }
        //printf("\n");
    }
    /*for(int i = 0;i<cantidadObjetos+2;i++){
        for(int j = 0; j< cantidadObjetos+1;j++){

            printf("%f  ",tablaResultado[i][j] );
        }
        printf("\n");
    }*/

    int i = 1;
    int j = 2;
    int k = 2;
    while(k < cantidadObjetos+1){
        
            for(j = k;j<cantidadObjetos+1;j++){
                pumpumpum(i,j);
                i++;
            }
            
        i =1;
        k++;
    }
    /*for(int i = 0;i<cantidadObjetos+2;i++){
        for(int j = 0; j< cantidadObjetos+1;j++){

            printf("%f  ",tablaResultado[i][j] );
        }
        printf("\n");
    }*/
    
    for(int i = 0;i<cantidadObjetos;i++){ 
        gtk_entry_set_text(gtk_grid_get_child_at(gridt,0,i+1),strsAux[i]);
    }
  
    CrearTabla();
    CrearTabla2();
}

void on_SalirDelPrograma_clicked()
{
    gtk_widget_destroy(window_SD);
}

int pumpumpum(int i, int j){

    int k = 0;
            float temp1;

            for(k = i; k<=j;k++){
  
                temp1 = tablaResultado[i][k-1] + tablaResultado[k+1][j];
                for(int p = i;p <= j;p++){
                    temp1 += promedios[p-1][0];
                }
                /*printf("A[%d][%d-1]: %f\n",i,j,tablaResultado[i][k-1]);
                printf("A[%d+1][%d]: %f\n",i,j,tablaResultado[k+1][j]);
                printf("i          : %f\n",promedios[i-1][0]);
                printf("j          : %f\n",promedios[j-1][0]);
                printf("sumaresult : %f\n\n", temp1);*/
                if(tablaResultado[i][j]==0){
                    tablaResultado[i][j]=temp1;
                    tablaResultadoAux[i][j]=k;
                }
                else if(tablaResultado[i][j]>temp1){
                    tablaResultado[i][j]=temp1;
                    tablaResultadoAux[i][j]=k;
                }

            }
            

            
  

}

void CrearTabla(){
     grid2 = gtk_grid_new ();
    gtk_grid_set_row_spacing (grid2, 1);
    gtk_grid_set_column_spacing (grid2, 1);

    for (int i = 0; i <= cantidadObjetos+1; i++)
    {
        for(int j = -1; j < cantidadObjetos; j++)
        {   
            if(i==j+2){
                        char val[30];
                        sprintf(val,"%d", 0);

                        label = gtk_label_new (val);
                        gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos+ 2));

                        box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                                            
                        gdk_color_parse( "#AFC6EE", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);  
                    }
            if(i==0){
                if(j==-1){
                    char val[30];
                    sprintf(val,"%d", 0);
                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos + 2));
                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                        
                    gdk_color_parse( "#467DD9", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);  
                }else{
                    char val[30];
                    sprintf(val,"%d", j+1);
                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos + 2));
                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                        
                    gdk_color_parse( "#467DD9", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);  
                }
            }
            else{
                if(j==-1){
                    char val[30];
                    sprintf(val,"%d", i);

                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos + 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    gdk_color_parse( "#AFC6EE", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);
                }
                
                else{  
                    if(tablaResultado[i][j+1]!=0){  
                        char val[30];
                        sprintf(val,"%f", tablaResultado[i][j+1]);

                        label = gtk_label_new (val);
                        gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos+ 2));

                        box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                                            
                        gdk_color_parse( "#AFC6EE", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);  } 
                    }
                    if(i==j){
                        char val[30];
                        sprintf(val,"%d", 0);

                        label = gtk_label_new (val);
                        gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos+ 2));

                        box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                                            
                        gdk_color_parse( "#AFC6EE", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);  
                    }
            }
        }
    }

    gtk_container_add (GTK_CONTAINER (tabla_solucion), grid2);
    gtk_widget_show (grid2);   
    
}

void CrearTabla2(){
     grid2 = gtk_grid_new ();
    gtk_grid_set_row_spacing (grid2, 1);
    gtk_grid_set_column_spacing (grid2, 1);

    for (int i = 0; i <= cantidadObjetos+1; i++)
    {
        for(int j = -1; j < cantidadObjetos; j++)
        {   
            if(i==j+2){
                        char val[30];
                        sprintf(val,"%d", 0);

                        label = gtk_label_new (val);
                        gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos+ 2));

                        box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                                            
                        gdk_color_parse( "#AFC6EE", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);  
                    }
            if(i==0){
                if(j==-1){
                    char val[30];
                    sprintf(val,"%d", 0);
                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos + 2));
                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                        
                    gdk_color_parse( "#467DD9", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);  
                }else{
                    char val[30];
                    sprintf(val,"%d", j+1);
                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos + 2));
                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                        
                    gdk_color_parse( "#467DD9", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);  
                }
            }
            else{
                if(j==-1){
                    char val[30];
                    sprintf(val,"%d", i);

                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos + 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    gdk_color_parse( "#AFC6EE", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);
                }
                
                else{  
                    if(tablaResultado[i][j+1]!=0){  
                        char val[30];
                        sprintf(val,"%d", tablaResultadoAux[i][j+1]);

                        label = gtk_label_new (val);
                        gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos+ 2));

                        box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                                            
                        gdk_color_parse( "#AFC6EE", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);  } 
                    }
                    if(i==j){
                        char val[30];
                        sprintf(val,"%d", 0);

                        label = gtk_label_new (val);
                        gtk_widget_set_size_request(label, 470/(cantidadObjetos + 2), 470/(cantidadObjetos+ 2));

                        box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                                            
                        gdk_color_parse( "#AFC6EE", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+2, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);  
                    }
            }
        }
    }

    gtk_container_add (GTK_CONTAINER (tabla_R), grid2);
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
    const gchar *cant_nodos;
    for(int i=1;i<=cantidadObjetos;i++){ 
        for(int j=0;j<2;j++){
            const gchar *cant_nodos;
            cant_nodos = gtk_entry_get_text(gtk_grid_get_child_at (gridt,j,i));
            fprintf(file, "%s\n", cant_nodos);
            
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



void readFile(char* filename)
{    

    FILE *file;
    file = fopen(filename, "r");
    char array[100];

    fgets(array, sizeof(array), file);
    strip(array);
    cantidadObjetos = atoi(array);
    gtk_entry_set_text(cantObj,array);

    on_acept_clicked();

    for(int i=1;i<=cantidadObjetos;i++){ 
        for(int j=0;j<2;j++){        

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
    gtk_label_set_text(GTK_LABEL(result), "");
    const gchar *pln;
    pln = gtk_entry_get_text(cantObj);
    cantidadObjetos = atoi(pln);

    if(strlen(pln)==0){
        gtk_label_set_text(GTK_LABEL(result), "Debe de especificar una cantidad de objetos.");
        return 0;
    }


    if(cantidadObjetos <= 0 ||cantidadObjetos > 100){
        gtk_label_set_text(GTK_LABEL(result), "La cantidad de llaves tiene que ser mayor que 0 y menor que 100.");
        return 0;
    }


    gridt = gtk_grid_new ();
    gtk_grid_set_row_spacing (gridt, 15);
    gtk_grid_set_column_spacing (gridt, 15);
    char v[5];

    for (int i = 0; i < cantidadObjetos+1; i++)
    {
        
        for(int j = 0; j < 2; j++)
        {               
            if(i==0){ 
                GtkWidget *labelf = gtk_label_new (strs[j]);  
                gtk_grid_attach(GTK_GRID(gridt), labelf, j, 0, 1, 1);
                gtk_widget_show (labelf);}     
            else if(j==0){
                GtkWidget *entry = gtk_entry_new();
            gtk_entry_set_width_chars(entry,6);
            gtk_grid_attach(GTK_GRID(gridt), entry, j, i, 1, 1);
            gtk_widget_show (entry);
            }
            else if(i!=0){
            GtkWidget *entry = gtk_entry_new();
            gtk_entry_set_width_chars(entry,4);
            gtk_grid_attach(GTK_GRID(gridt), entry, j, i, 1, 1);
            gtk_widget_show (entry);}
        }
    }
    gtk_container_add (GTK_CONTAINER (tabla_input), gridt);
    gtk_widget_show (gridt);

   
}


