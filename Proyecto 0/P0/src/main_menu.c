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

 


GtkBuilder      *builder_about; 
GtkWidget       *about_window;

GtkBuilder      *builder_Programa1; 
GtkWidget       *window_Programa1;

GtkWidget *P1;
GtkWidget *P2;
GtkWidget *P3;
GtkWidget *P4;
GtkWidget *P5;
GtkWidget *P6;


GtkWidget *btn_Salir;
GtkWidget *btn_AcercaDe;

GtkWidget *button_1;
GtkWidget *button_2;
GtkWidget *button_3;
GtkWidget *button_4;
GtkWidget *button_5;
GtkWidget *button_6;


int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/Menu_Principal.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "ventana"));
    gtk_builder_connect_signals(builder, NULL);

    P1 = GTK_WIDGET(gtk_builder_get_object(builder, "p1"));
    P2 = GTK_WIDGET(gtk_builder_get_object(builder, "p2"));
    P3 = GTK_WIDGET(gtk_builder_get_object(builder, "p3"));
    P4 = GTK_WIDGET(gtk_builder_get_object(builder, "p4"));
    P5 = GTK_WIDGET(gtk_builder_get_object(builder, "p5"));
    P6 = GTK_WIDGET(gtk_builder_get_object(builder, "p6"));

    btn_Salir = GTK_WIDGET(gtk_builder_get_object(builder, "btnSalir"));
    btn_AcercaDe = GTK_WIDGET(gtk_builder_get_object(builder, "btnAcerca"));

	gtk_widget_set_tooltip_text(P1, "Inicia el programa del algoritmo Floyd-Warshall, el cual encuentra la ruta mas corta para llegar de un punto a otro en grafos dirigidos ponderados.");
    gtk_widget_set_tooltip_text(P2, "Inicia el programa del algoritmo Knapsack problem, el cual busca encontrar la mejor solución con un conjunto de posibilidades a las cuales tienen un valor y un costo(peso), existe una 'mochila' con capacidad conocida para transportar los objetos, por lo que se debe maximizar la ganancia sin exceder el límite.");
    gtk_widget_set_tooltip_text(P3, "TBA");
    gtk_widget_set_tooltip_text(P4, "TBA");
    gtk_widget_set_tooltip_text(P5, "TBA");
    gtk_widget_set_tooltip_text(P6, "Termina el programa");
 	
 	gtk_widget_set_tooltip_text(btn_Salir, "Termina el programa");
    gtk_widget_set_tooltip_text(btn_AcercaDe, "Muestra información del programa y los miembros del equipo");
   


  
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}

void on_btnP1Comenzar_clicked()
{
    system("./Pending &");
}

void on_btnP2Comenzar_clicked()
{
    system("./Pending &");
}

void on_btnP3Comenzar_clicked()
{
    system("./Pending &");
}

void on_btnP4Comenzar_clicked()
{
    system("./Pending &");
}

void on_btnP5Comenzar_clicked()
{
    system("./Pending &");
}
void on_btnAcerca_clicked()
{
    system("./Acerca &");
}
void on_btnSalir_clicked()
{
    gtk_main_quit();
}

