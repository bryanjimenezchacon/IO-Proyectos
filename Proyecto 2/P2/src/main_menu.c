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

	gtk_widget_set_tooltip_text(P1, "Inicia el programa del algoritmo Floyd-Warshall. El problema que intenta resolver este algoritmo es el de encontrar el camino más corto entre todos los pares de nodos o vértices de un grafo. Esto es semejante a construir una tabla con todas las distancias mínimas entre pares de ciudades de un mapa, indicando además la ruta a seguir para ir de la primera ciudad a la segunda. Este es uno de los problemas más interesantes que se pueden resolver con algoritmos de grafos.");
    gtk_widget_set_tooltip_text(P2, "Inicia el programa del algoritmo Knapsack problem, es un problema de optimización combinatoria, porque que busca la mejor solución entre un conjunto finito de posibles soluciones a un problema. Modela una situación de llenar una mochila, que tiene una capacidad determinada fija, y hay un conjunto de objetos, cada uno con un peso y valor específicos. Los objetos colocados en la mochila deben maximizar el valor total sin exceder el peso máximo.");
    gtk_widget_set_tooltip_text(P3, "TBA");
    gtk_widget_set_tooltip_text(P4, "TBA");
    gtk_widget_set_tooltip_text(P5, "TBA");
    gtk_widget_set_tooltip_text(P6, "Termina el programa");
    gtk_widget_set_tooltip_text(btn_Salir, "Termina el programa");
    gtk_widget_set_tooltip_text(btn_AcercaDe, "Muestra información del programa y los miembros del equipo");
   


  
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    exit(3);
    return 0;
}

void on_btnP1Comenzar_clicked()
{
    system("./Rutas_Optimas &");
}

void on_btnP2Comenzar_clicked()
{
    system("./Mochila &");
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

