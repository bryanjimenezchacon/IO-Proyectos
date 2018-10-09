/************************************************************************
# 
# Instituto Tecnológico de Costa Rica
# Investigación de Operaciones Gr 40
#
#
# Proyecto 4.Reemplazo de Equipos
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

GtkWidget *folder;
GtkWidget *filenameEntry;
GtkWidget *guardar;
GtkWidget *tabla_input;

GtkWidget *table;
GtkWidget *SalirDelPrograma;

GtkWidget *tabla_planAux;
GtkWidget *calculos;
GtkWidget *grid1;
GtkWidget *grid2;
GtkWidget *gridt;

GtkWidget *result;
GtkWidget *resultplanes;

GtkWidget *plan;
GtkWidget *costo;
GtkWidget *vidaU;

GtkWidget *label;
GtkWidget *box;


char *strs[50]= {"Años","Mantenimiento","Reventa"};
char *strs2[50]= {"t","G(t)","Próximo"};


int ** tabla;
int ** tablaC;
int ** tablaG;
int ** tablaReventa;
int ** tablaPlan;
int ** tablaPlanAux;

int contador = 0;


int costoini = 0;
int tiempototal = -1;
int vidaUtil = 1;
char val[3000000];

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/Reemplazo_Equipos.glade", NULL);
 
    window_SD = GTK_WIDGET(gtk_builder_get_object(builder, "window_SD"));

    gtk_builder_connect_signals(builder, NULL);   
    entry_cargar_SD = GTK_WIDGET(gtk_builder_get_object(builder, "entry_cargar_SD"));
    folder = GTK_WIDGET(gtk_builder_get_object(builder, "folder"));
    filenameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "filename"));
    guardar = GTK_WIDGET(gtk_builder_get_object(builder, "guardar_SD"));
    btn_cargar_SD = GTK_WIDGET(gtk_builder_get_object(builder, "btn_cargar_SD"));
    SalirDelPrograma = GTK_WIDGET(gtk_builder_get_object(builder, "SalirDelPrograma"));

    plan = GTK_WIDGET(gtk_builder_get_object(builder, "plan"));
    vidaU = GTK_WIDGET(gtk_builder_get_object(builder, "vidaU"));
    costo = GTK_WIDGET(gtk_builder_get_object(builder, "costo"));
    result = GTK_WIDGET(gtk_builder_get_object(builder, "result"));
    resultplanes = GTK_WIDGET(gtk_builder_get_object(builder, "resultplanes"));
    tabla_planAux = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_planAux"));
    tabla_input = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_input"));
    calculos = GTK_WIDGET(gtk_builder_get_object(builder, "calculos"));
	
    gtk_widget_set_tooltip_text(entry_cargar_SD, "Seleccionar un archivo");
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

void calcularC(){
    char v[12];
    int limitador = 0;
    int reg = 0;
    strcpy(val,"");
    for(int i = 0;i <= vidaUtil;i++){
        limitador++;
        for(int j = 0;j < tiempototal;j++){
            if(vidaUtil<limitador){
                continue;
            }
            if(j+limitador+i-reg>tiempototal){
                continue;
            }
            strcat(val,"C");
            sprintf(v,"%d|%d",j+i-reg, j+limitador+i-reg);
            strcat(val,v);
            strcat(val," = ");
            if(j+limitador+i-reg>tiempototal-1){
                int tempo = costoini;
                for(int r = 0; r < limitador;r++){
                    tempo+=tabla[r][0];
                }
                tempo-=tabla[i][1];
                tablaC[i][0]=tempo;
                sprintf(v,"%d",tempo);
                strcat(val,v);   
            }
        }
        reg++;
        strcat(val,"\n");
    }
    strcat(val,"\n");
    
}

void calcularG(){
    char v[12];
    int reg = 0;
    
    for(int i = 0;i <= tiempototal;i++){
        strcat(val,"\nG(");
        sprintf(v,"%d",tiempototal-i);
        strcat(val,v);
        strcat(val,") = ");
        if(i==0){
            strcat(val,"0\n");
            tablaG[i][0]=0;
            continue;
        }
        
        int tempmenor = -1;
  
        tablaPlanAux = createFloatMatrix(tiempototal+1, 1);

        for(int j = 1;j <= vidaUtil;j++){
            int temp = tablaC[j-1][0] + tablaG[i-j][0];
            strcat(val,"\nC");
            sprintf(v,"%d|",tiempototal-i);
            strcat(val,v);
            sprintf(v,"%d",tiempototal-(i-j));
            strcat(val,v);
            strcat(val," + G(");
            sprintf(v,"%d) = ",tiempototal-(i-j));
            strcat(val,v);
            sprintf(v,"%d + ",tablaC[j-1][0]);
            strcat(val,v);
            sprintf(v,"%d = ",tablaG[i-j][0]);
            strcat(val,v);

            sprintf(v,"%d",temp);
            strcat(val,v);
            tablaPlanAux[j-1][0] = temp;

            if(tempmenor==-1){
                tempmenor = temp;
            }

            if(tempmenor>temp){
                tempmenor = temp;   
            }
            
            if(i==j){
                break;
            }
        }
        
        revisarMenor(tempmenor, i);

        tablaG[i][0] = tempmenor;
        strcat(val,"\n");
        reg++;
    }
    gtk_label_set_text(GTK_LABEL(calculos), val);
}

void revisarMenor(int tempmenor, int i){
    for(int j = 1; j <= tiempototal;j++){
        if(tablaPlanAux[j-1][0]==tempmenor){
            tablaPlan[tiempototal-i][tiempototal-i+j]=tiempototal-i+j;
        }
    }
}


int on_btn_calcular_clicked(){

	deleteTablesGrid(tabla_planAux);
	gtk_label_set_text(GTK_LABEL(calculos), "");
    gtk_label_set_text(GTK_LABEL(resultplanes), "");

	tabla = createFloatMatrix(tiempototal, 2);
	tablaC = createFloatMatrix(tiempototal, 1);
    tablaG = createFloatMatrix(tiempototal+1, 1);
    tablaPlan = createFloatMatrix(tiempototal+1, tiempototal+1);


    for(int i=1;i<=vidaUtil;i++){ 
        for(int j=2;j<4;j++){
            
                const gchar *cant_nodos;
                cant_nodos = gtk_entry_get_text(gtk_grid_get_child_at (gridt,j,i));
                int valor = atoi(cant_nodos);
                if(isdigit(cant_nodos[0])==FALSE){
                    gtk_label_set_text(GTK_LABEL(result), "Los valores de la tabla no pueden tener letras.");
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
    calcularC();
    calcularG();
    CrearTabla();
    sprintf(val,"%s","");
    for(int t = 0;t < tiempototal;t++){
        char v[10];
        strcat(val,"Planes desde año ");
        sprintf(v,"%d",t);
        strcat(val,v);
        strcat(val,": \n");
        mostrarPlanes(t);
    }
    gtk_label_set_text(GTK_LABEL(resultplanes), val);
}

int mostrarPlanes(int ind){
    char v[30];
    if(ind == tiempototal){
        strcat(val,"\n");
        return 0;
    }

    //for(int i = ind;i <= tiempototal; i++){
        for(int j = 0; j<=tiempototal; j++){
            if(tablaPlan[ind][j]!=0){
                sprintf(v,"%d -> ",ind);
                strcat(val,v);
                sprintf(v,"%d\n",tablaPlan[ind][j]);
                strcat(val,v);
                mostrarPlanes(tablaPlan[ind][j]);
            }
        }
    //}
}

void SignalSalir()
{
    gtk_widget_destroy(GTK_WIDGET(window_SD));
}
//borrar
void on_SalirDelPrograma_clicked()
{
    gtk_widget_destroy(window_SD);
}
//

void CrearTabla(){
                   
    grid2 = gtk_grid_new ();
    gtk_grid_set_row_spacing (grid2, 1);
    gtk_grid_set_column_spacing (grid2, 1);

    for (int i = -1; i < tiempototal+1; i++)
    {
        for(int j = 0; j < 3; j++)
        {   

            if(i==-1){
                char val[30];
                sprintf(val,"%s", strs2[j]);
                label = gtk_label_new (val);
                gtk_widget_set_size_request(label, 470/(tiempototal + 2), 470/(tiempototal + 2));
                box = gtk_box_new(0, 0);
                gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                const GdkRGBA *color;
                    
                gdk_color_parse( "#467DD9", &color );
                gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                gtk_widget_show (label);
                gtk_widget_show (box);  
            }
            else{
                if(j==0){
                    char val[30];
                    sprintf(val,"%d", i);

                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(tiempototal + 2), 470/(tiempototal + 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    gdk_color_parse( "#AFC6EE", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);
                }
                else if(j==2){
                    sprintf(val,"%s", "");
                    char v[100];
                    for(int r = 0; r <= tiempototal;r++){

                        if(tablaPlan[i][r]!=0){
                            sprintf(v,"%d", tablaPlan[i][r]);
                            if(r+1!=tiempototal){
                                strcat(v,", ");
                            }
                            strcat(val,v);
                        }
                    }
                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(tiempototal + 2), 470/(tiempototal+ 2));

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
                    char val[30];
                    sprintf(val,"%d", tablaG[tiempototal-i][0]);

                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 470/(tiempototal + 2), 470/(tiempototal+ 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                                        
                    gdk_color_parse( "#AFC6EE", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);   
                }
            }
        }
    }

    gtk_container_add (GTK_CONTAINER (tabla_planAux), grid2);
    gtk_widget_show (grid2);   
    
}
//borrar
int on_guardar_SD_clicked ()
{
    if(tiempototal==-1){
    	gtk_label_set_text(GTK_LABEL(result), "Tiene que poner la información primero");
        return 0;
    }

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
//
void SignalAbrir(gpointer window)
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

void writeFile(char* filename)
{

    FILE *file;
    file = fopen(filename, "w");

    fprintf(file, "%i\n", tiempototal);
    fprintf(file, "%i\n", costoini);
    fprintf(file, "%i\n", vidaUtil);
	const gchar *cant_nodos;
    for(int i=1;i<=vidaUtil;i++){ 
        for(int j=2;j<4;j++){
            const gchar *cant_nodos;
            cant_nodos = gtk_entry_get_text(gtk_grid_get_child_at (gridt,j,i));
            int valor = atoi(cant_nodos);
    		fprintf(file, "%i\n", valor);
    	}
    }

    fclose(file);
}


//borrar
int on_btn_cargar_SD_clicked(){
    const gchar *filename;
    filename = gtk_file_chooser_get_filename (entry_cargar_SD);
    if(filename==NULL){

        gtk_label_set_text(GTK_LABEL(result), "Selecione un archivo.");
        return 0;
    }
    readFile(filename);
}

//

void readFile(char* filename)
{    

    FILE *file;
    file = fopen(filename, "r");
    char array[10];
    fgets(array, sizeof(array), file);
    strip(array);
    //fscanf(file, "%i", &tiempototal);
    tiempototal = atoi(array);
    gtk_entry_set_text(plan,array);

    fgets(array, sizeof(array), file);
    strip(array);

    costoini = atoi(array);
    gtk_entry_set_text(costo,array);
    

    fgets(array, sizeof(array), file);
    strip(array);
    
    vidaUtil = atoi(array);

    gtk_combo_box_set_active(vidaU,vidaUtil-1);
    on_aceptPlan_clicked();


    for(int i=1;i<=vidaUtil;i++){ 
        for(int j=2;j<4;j++){         

            fgets(array, sizeof(array), file);
            strip(array); //Quita espacios null
            gtk_entry_set_text(gtk_grid_get_child_at(gridt,j,i),array);
        }
    }


    fclose(file);
    

   


 
}



void on_vidaUtil_changed(GtkWidget *widget){
    GtkComboBox *combo_box = widget;
    vidaUtil = gtk_combo_box_get_active (combo_box)+1;
}

int on_aceptPlan_clicked(){
    
    deleteTablesGrid(tabla_input);    
    gtk_label_set_text(GTK_LABEL(result), "");

    const gchar *pln;
    pln = gtk_entry_get_text(plan);
    int t = atoi(pln);
    
    pln = gtk_entry_get_text(costo);
    int c = atoi(pln);

    if(c<=0){
        gtk_label_set_text(GTK_LABEL(result), "El costo tiene que ser mayor que 0.");
        return 0;
    }
    if(t<=0||t > 50){
        gtk_label_set_text(GTK_LABEL(result), "El plan tiene que ser mayor que 0 y menor que 50");
        return 0;
    }
    costoini = c;
    tiempototal = t;

    if(vidaUtil >= tiempototal){
        vidaUtil = tiempototal;
        gtk_combo_box_set_active(vidaU,tiempototal-1);
    }

    gridt = gtk_grid_new ();
    gtk_grid_set_row_spacing (gridt, 5);
    gtk_grid_set_column_spacing (gridt, 5);
    char v[5];

    for (int i = 0; i <= vidaUtil; i++)
    {
        
        for(int j = 0; j < 4; j++)
        {               
            if(i==0){ 
                GtkWidget *labelf = gtk_label_new (strs[j-1]);  
                gtk_grid_attach(GTK_GRID(gridt), labelf, j, 0, 1, 1);
                gtk_widget_show (labelf);}     
            if(j==1&&i!=0){              
                sprintf(v,"%d",i);
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




