
#include <gtk/gtk.h>

 


GtkBuilder      *builder_about; 
GtkWidget       *about_window;

GtkBuilder      *builder_Programa1; 
GtkWidget       *window_Programa1;

GtkWidget *Programa1;
GtkWidget *Programa2;
GtkWidget *Programa3;
GtkWidget *Programa4;
GtkWidget *Programa5;
GtkWidget *Programa6;

GtkWidget *btn_Salir;
GtkWidget *btn_About;

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



  
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}



