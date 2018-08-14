
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

	gtk_widget_set_tooltip_text(P1, "Conocido como Algoritmo de Floyd, el cual determina determina la ruta más corta entre dos nodos cualquiera de la red.");
    gtk_widget_set_tooltip_text(P2, "Conocido como Knapsack problem, el cual busca la mejor solución entre un conjunto finito de posibles soluciones a un problema. Modela una situación en la cual hay que llenar una mochila, incapaz de soportar más de un peso determinado, cada objeto a colocar en la mochila tiene un peso y valor específicos,los objetos colocados en la mochila deben maximizar el valor total sin exceder el peso máximo.");
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
void on_btnSalir_clicked()
{
    gtk_main_quit();
}

