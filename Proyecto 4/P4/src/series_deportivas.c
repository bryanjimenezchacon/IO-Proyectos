/************************************************************************
# 
# Instituto Tecnológico de Costa Rica
# Investigación de Operaciones Gr 40
#
#
# Proyecto 3.Series Deportivas
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
GtkWidget  *window;
GtkWidget *cantJuegos;
GtkWidget *g_Ph;
GtkWidget *g_Pr;
GtkWidget *Acept;
GtkWidget * btn_cargar_SD;

GtkWidget *juego1;
GtkWidget *juego2;
GtkWidget *juego3;
GtkWidget *juego4;
GtkWidget *juego5;
GtkWidget *juego6;
GtkWidget *juego7;
GtkWidget *juego8;
GtkWidget *juego9;
GtkWidget *juego10;
GtkWidget *juego11;

GtkWidget *probabilidades1;
GtkWidget *probabilidades2;
GtkWidget *result;
GtkWidget *entry_cargar_SD;
GtkWidget *btn_calcular_SD;

GtkWidget *folder;
GtkWidget *filenameEntry;
GtkWidget *guardar;


GtkWidget *SalirDelPrograma;

GtkWidget *datos_SD;
GtkWidget *tabla_sol_SD;
GtkWidget *tabla_nuevo_SD;
GtkWidget * grid2;
GtkWidget *scaleCasa, *scaleVisita;


GtkWidget *A1, *A2, *A3, *A4, *A5, *A6, *A7, *A8, *A9, *A10, *A11, *B1, *B2, *B3 , *B4, *B5, *B6, *B7, *B8, *B9, *B10, *B11, *C3, *C5, *C7, *C9, *C11;
GtkWidget *L1, *L2, *L3, *L4, *L5, *L6, *L7, *L8, *L9, *L10, *L11;



GtkWidget *label;
GtkWidget *box;

int mitadJuegos = 3;
int totalJuegos = 3;
float ph = 0;
float pr = 0;
float qh = 0;
float qr = 0;

float ** tabla;
float resp;


int lugar_juego[11];

float mat[10][10];

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/Equipos.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_builder_connect_signals(builder, NULL); 

    A1 = GTK_WIDGET(gtk_builder_get_object(builder, "A1"));
    A2 = GTK_WIDGET(gtk_builder_get_object(builder, "A2"));
    A3 = GTK_WIDGET(gtk_builder_get_object(builder, "A3"));
    A4 = GTK_WIDGET(gtk_builder_get_object(builder, "A4"));
    A5 = GTK_WIDGET(gtk_builder_get_object(builder, "A5"));
    A6 = GTK_WIDGET(gtk_builder_get_object(builder, "A6"));
    A7 = GTK_WIDGET(gtk_builder_get_object(builder, "A7"));
    A8 = GTK_WIDGET(gtk_builder_get_object(builder, "A8"));
    A9 = GTK_WIDGET(gtk_builder_get_object(builder, "A9"));
    A10 = GTK_WIDGET(gtk_builder_get_object(builder, "A10"));
    A11 = GTK_WIDGET(gtk_builder_get_object(builder, "A11"));

    B1 = GTK_WIDGET(gtk_builder_get_object(builder, "B1"));
    B2 = GTK_WIDGET(gtk_builder_get_object(builder, "B2"));
    B3 = GTK_WIDGET(gtk_builder_get_object(builder, "B3"));
    B4 = GTK_WIDGET(gtk_builder_get_object(builder, "B4"));
    B5 = GTK_WIDGET(gtk_builder_get_object(builder, "B5"));
    B6 = GTK_WIDGET(gtk_builder_get_object(builder, "B6"));
    B7 = GTK_WIDGET(gtk_builder_get_object(builder, "B7"));
    B8 = GTK_WIDGET(gtk_builder_get_object(builder, "B8"));
    B9 = GTK_WIDGET(gtk_builder_get_object(builder, "B9"));
    B10 = GTK_WIDGET(gtk_builder_get_object(builder, "B10"));
    B11 = GTK_WIDGET(gtk_builder_get_object(builder, "B11"));

    L1 = GTK_WIDGET(gtk_builder_get_object(builder, "L1"));
    L2 = GTK_WIDGET(gtk_builder_get_object(builder, "L2"));
    L3 = GTK_WIDGET(gtk_builder_get_object(builder, "L3"));
    L4 = GTK_WIDGET(gtk_builder_get_object(builder, "L4"));
    L5 = GTK_WIDGET(gtk_builder_get_object(builder, "L5"));
    L6 = GTK_WIDGET(gtk_builder_get_object(builder, "L6"));
    L7 = GTK_WIDGET(gtk_builder_get_object(builder, "L7"));
    L8 = GTK_WIDGET(gtk_builder_get_object(builder, "L8"));
    L9 = GTK_WIDGET(gtk_builder_get_object(builder, "L9"));
    L10 = GTK_WIDGET(gtk_builder_get_object(builder, "L10"));
    L11 = GTK_WIDGET(gtk_builder_get_object(builder, "L11"));

    C3 = GTK_WIDGET(gtk_builder_get_object(builder, "C3"));
    C5 = GTK_WIDGET(gtk_builder_get_object(builder, "C5"));
    C7 = GTK_WIDGET(gtk_builder_get_object(builder, "C7"));
    C9 = GTK_WIDGET(gtk_builder_get_object(builder, "C9"));
    C11 = GTK_WIDGET(gtk_builder_get_object(builder, "C11"));

    scaleCasa = GTK_WIDGET(gtk_builder_get_object(builder, "scaleCasa"));
    scaleVisita = GTK_WIDGET(gtk_builder_get_object(builder, "scaleVisita"));

    

    
    probabilidades1 = GTK_WIDGET(gtk_builder_get_object(builder, "probabilidades1"));
    probabilidades2 = GTK_WIDGET(gtk_builder_get_object(builder, "probabilidades2"));

    result = GTK_WIDGET(gtk_builder_get_object(builder, "result"));
    btn_calcular_SD = GTK_WIDGET(gtk_builder_get_object(builder, "btn_calcular_SD"));
    tabla_sol_SD = GTK_WIDGET(gtk_builder_get_object(builder, "tabla_sol_SD"));


    gtk_widget_set_tooltip_text(btn_calcular_SD, "Calcula la tabla con las probabilidades de A y B");
    g_object_unref(builder);
    botonesVacios();
    gtk_widget_show(window);
                             
    gtk_main();
    return 0;
} 

void botonesVacios()
{
    gtk_button_set_image (GTK_BUTTON (A1), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A2), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A3), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A4), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A5), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A6), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A7), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A8), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A9), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A10), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (A11), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B1), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B2), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B3), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B4), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B5), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B6), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B7), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B8), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B9), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B10), gtk_image_new_from_file ("glade/Vacio.png"));
    gtk_button_set_image (GTK_BUTTON (B11), gtk_image_new_from_file ("glade/Vacio.png"));


}

void ocultar(int c)
{

    switch(c) {
      case 3 :
        gtk_widget_set_visible (GTK_LABEL(L1), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L2), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L3), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L4), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L5), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L6), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L7), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L8), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L9), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L10), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L11), FALSE);

        gtk_widget_set_visible (GTK_BUTTON(A1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A4), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A5), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A6), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A7), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A8), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A9), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A10), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A11), FALSE);

        gtk_widget_set_visible (GTK_BUTTON(B1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B4), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B5), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B6), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B7), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B8), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B9), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B10), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B11), FALSE);
         break;

      case 5 :
        gtk_widget_set_visible (GTK_LABEL(L1), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L2), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L3), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L4), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L5), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L6), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L7), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L8), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L9), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L10), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L11), FALSE);

        gtk_widget_set_visible (GTK_BUTTON(A1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A4), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A5), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A6), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A7), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A8), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A9), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A10), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A11), FALSE);

        gtk_widget_set_visible (GTK_BUTTON(B1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B4), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B5), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B6), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B7), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B8), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B9), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B10), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B11), FALSE);


        break;

      case 7 :
        gtk_widget_set_visible (GTK_LABEL(L1), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L2), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L3), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L4), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L5), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L6), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L7), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L8), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L9), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L10), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L11), FALSE);

        gtk_widget_set_visible (GTK_BUTTON(A1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A4), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A5), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A6), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A7), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A8), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A9), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A10), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A11), FALSE);

        gtk_widget_set_visible (GTK_BUTTON(B1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B4), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B5), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B6), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B7), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B8), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B9), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B10), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B11), FALSE);
         break;

       case 9 :
        gtk_widget_set_visible (GTK_LABEL(L1), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L2), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L3), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L4), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L5), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L6), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L7), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L8), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L9), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L10), FALSE);
        gtk_widget_set_visible (GTK_LABEL(L11), FALSE);

        gtk_widget_set_visible (GTK_BUTTON(A1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A4), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A5), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A6), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A7), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A8), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A9), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A10), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(A11), FALSE);

        gtk_widget_set_visible (GTK_BUTTON(B1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B4), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B5), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B6), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B7), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B8), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B9), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B10), FALSE);
        gtk_widget_set_visible (GTK_BUTTON(B11), FALSE);
         break;

        case 11: 
        gtk_widget_set_visible (GTK_LABEL(L1), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L2), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L3), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L4), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L5), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L6), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L7), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L8), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L9), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L10), TRUE);
        gtk_widget_set_visible (GTK_LABEL(L11), TRUE);

        gtk_widget_set_visible (GTK_BUTTON(A1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A4), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A5), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A6), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A7), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A8), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A9), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A10), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(A11), TRUE);

        gtk_widget_set_visible (GTK_BUTTON(B1), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B2), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B3), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B4), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B5), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B6), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B7), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B8), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B9), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B10), TRUE);
        gtk_widget_set_visible (GTK_BUTTON(B11), TRUE);
         break;

      default :
         printf("Invalid grade\n" );
     }
}

void SignalSalir()
{
    gtk_widget_destroy(GTK_WIDGET(window));
}



void uncheck(int c)
{

    switch(c) {
      case 3 :
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C5), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C7), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C9), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C11), FALSE);
         break;
      case 5 :
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C3), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C7), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C9), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C11), FALSE);
        break;
      case 7 :
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C3), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C5), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C9), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C11), FALSE);
         break;
      case 9 :
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C3), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C5), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C7), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C11), FALSE);
         break;
      case 11 : 
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C3), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C5), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C7), FALSE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C9), FALSE);
         break;
      default :
         printf("Invalid grade\n" );
     }
   
}

void on_C3_toggled()
{
    if(gtk_toggle_button_get_active(C3)){
        uncheck(3);
        ocultar(3);
    }
    
    totalJuegos = 3;
    mitadJuegos = 3;
}

void on_C5_toggled()
{
    if(gtk_toggle_button_get_active(C5)){
        uncheck(5);
        ocultar(5);
    }
    totalJuegos = 5;
    mitadJuegos = 4;
    

}

void on_C7_toggled()
{
    if(gtk_toggle_button_get_active(C7)){
        uncheck(7);
        ocultar(7);
    }
    totalJuegos = 7;
    mitadJuegos = 5;
    

}

void on_C9_toggled()
{
    if(gtk_toggle_button_get_active(C9)){
        uncheck(9);
        ocultar(9);
    }
    totalJuegos = 9;
    mitadJuegos = 6;
    

}

void on_C11_toggled()
{
    if(gtk_toggle_button_get_active(C11)){
        uncheck(11);
        ocultar(11);
    }
    totalJuegos = 11;
    mitadJuegos = 7;
    

}

void on_A1_clicked()
{
    if(lugar_juego[0] == 1){
        gtk_button_set_image (GTK_BUTTON (A1), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B1), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[0] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A1), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B1), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[0] = 1;
    }
    
}

void on_B1_clicked()
{
    if(lugar_juego[0] == 2){
        gtk_button_set_image (GTK_BUTTON (B1), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A1), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[0] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B1), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A1), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[0] = 2;
    }
    
}

void on_A2_clicked()
{
    if(lugar_juego[1] == 1){
        gtk_button_set_image (GTK_BUTTON (A2), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B2), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[1] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A2), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B2), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[1] = 1;
    }
    
}

void on_B2_clicked()
{
    if(lugar_juego[1] == 2){
        gtk_button_set_image (GTK_BUTTON (B2), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A2), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[1] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B2), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A2), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[1] = 2;
    }
    
}

void on_A3_clicked()
{
    if(lugar_juego[2] == 1){
        gtk_button_set_image (GTK_BUTTON (A3), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B3), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[2] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A3), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B3), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[2] = 1;
    }
    
}

void on_B3_clicked()
{
    if(lugar_juego[2] == 2){
        gtk_button_set_image (GTK_BUTTON (B3), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A3), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[2] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B3), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A3), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[2] = 2;
    }
    
}

void on_A4_clicked()
{
    if(lugar_juego[3] == 1){
        gtk_button_set_image (GTK_BUTTON (A4), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B4), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[3] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A4), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B4), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[3] = 1;
    }
    
}

void on_B4_clicked()
{
    if(lugar_juego[3] == 2){
        gtk_button_set_image (GTK_BUTTON (B4), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A4), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[3] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B4), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A4), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[3] = 2;
    }
    
}

void on_A5_clicked()
{
    if(lugar_juego[4] == 1){
        gtk_button_set_image (GTK_BUTTON (A5), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B5), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[4] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A5), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B5), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[4] = 1;
    }
    
}

void on_B5_clicked()
{
    if(lugar_juego[4] == 2){
        gtk_button_set_image (GTK_BUTTON (B5), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A5), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[4] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B5), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A5), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[4] = 2;
    }
    
}

void on_A6_clicked()
{
    if(lugar_juego[5] == 1){
        gtk_button_set_image (GTK_BUTTON (A6), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B6), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[5] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A6), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B6), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[5] = 1;
    }
    
}

void on_B6_clicked()
{
    if(lugar_juego[5] == 2){
        gtk_button_set_image (GTK_BUTTON (B6), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A6), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[5] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B6), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A6), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[5] = 2;
    }
    
}

void on_A7_clicked()
{
    if(lugar_juego[6] == 1){
        gtk_button_set_image (GTK_BUTTON (A7), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B7), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[6] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A7), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B7), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[6] = 1;
    }
    
}

void on_B7_clicked()
{
    if(lugar_juego[6] == 2){
        gtk_button_set_image (GTK_BUTTON (B7), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A7), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[6] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B7), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A7), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[6] = 2;
    }
    
}

void on_A8_clicked()
{
    if(lugar_juego[7] == 1){
        gtk_button_set_image (GTK_BUTTON (A8), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B8), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[7] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A8), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B8), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[7] = 1;
    }
    
}

void on_B8_clicked()
{
    if(lugar_juego[7] == 2){
        gtk_button_set_image (GTK_BUTTON (B8), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A8), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[7] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B8), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A8), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[7] = 2;
    }
    
}

void on_A9_clicked()
{
    if(lugar_juego[8] == 1){
        gtk_button_set_image (GTK_BUTTON (A9), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B9), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[8] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A9), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B9), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[8] = 1;
    }
    
}

void on_B9_clicked()
{
    if(lugar_juego[8] == 2){
        gtk_button_set_image (GTK_BUTTON (B9), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A9), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[8] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B9), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A9), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[8] = 2;
    }
    
}

void on_A10_clicked()
{
    if(lugar_juego[9] == 1){
        gtk_button_set_image (GTK_BUTTON (A10), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B10), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[9] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A10), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B10), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[9] = 1;
    }
    
}

void on_B10_clicked()
{
    if(lugar_juego[9] == 2){
        gtk_button_set_image (GTK_BUTTON (B10), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A10), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[9] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B10), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A10), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[9] = 2;
    }
    
}

void on_A11_clicked()
{
    if(lugar_juego[10] == 1){
        gtk_button_set_image (GTK_BUTTON (A11), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (B11), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[10] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (A11), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B11), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[10] = 1;
    }
    
}

void on_B11_clicked()
{
    if(lugar_juego[10] == 2){
        gtk_button_set_image (GTK_BUTTON (B11), gtk_image_new_from_file ("glade/Vacio.png"));
        gtk_button_set_image (GTK_BUTTON (A11), gtk_image_new_from_file ("glade/Vacio.png"));
        lugar_juego[10] = 0;
    }
    else{
        gtk_button_set_image (GTK_BUTTON (B11), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (A11), gtk_image_new_from_file ("glade/Rojo.png"));
        lugar_juego[10] = 2;
    }
    
}

void imprimirBotones()
{
    for(int i = 0; i < totalJuegos; i++)
    {
        g_print("%i", lugar_juego[i]);
    }
    g_print("%s\n", "");
}
 

void on_SalirDelPrograma_clicked()
{
    gtk_widget_destroy(window);
}



void CrearTabla(){
    int i, j;

    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(tabla_sol_SD));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
      gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);

                       
    grid2 = gtk_grid_new ();
    gtk_grid_set_row_spacing (grid2, 2);
    gtk_grid_set_column_spacing (grid2, 2);

                     


    for (i = -1; i < (mitadJuegos); i++)
    {
        for(j = -1; j < (mitadJuegos); j++)
        {
            if (i==-1){
                if(j==-1){
                    label = gtk_label_new ("");
                    gtk_widget_set_size_request(label, 700/(mitadJuegos+ 2), 700/(mitadJuegos+ 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    
                    gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);
                       
                }
                else{
                    char val[30];
                    sprintf(val,"%d", j);

                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 700/(mitadJuegos + 2), 700/(mitadJuegos + 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    gdk_color_parse( "#00BFFF", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);      
                }
            }
            else{
                if(j==-1){
                    char val[30];
                    sprintf(val,"%d", i);

                    label = gtk_label_new (val);
                    gtk_widget_set_size_request(label, 700/(mitadJuegos + 2), 700/(mitadJuegos + 2));

                    box = gtk_box_new(0, 0);
                    gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                    const GdkRGBA *color;
                    
                    gdk_color_parse( "#00BFFF", &color );
                    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                    gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                    gtk_widget_show (label);
                    gtk_widget_show (box);
                }
                else{
                    if((j==0)&&(i==0)){
                        label = gtk_label_new ("");
                        gtk_widget_set_size_request(label, 700/(mitadJuegos+ 2), 700/(mitadJuegos + 2));

                        box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                        
                        gdk_color_parse( "#A9D0F5", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);
                    }

                    if((i == mitadJuegos-1)&& (j == mitadJuegos-1 )){
                         char val[30];
                        sprintf(val,"%.*f", 4, tabla[i][j]);

                        label = gtk_label_new (val);
                        gtk_widget_set_size_request(label, 700/(mitadJuegos+ 2), 700/(mitadJuegos + 2));

                        box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                        
                        gdk_color_parse( "#9d1215", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);

                    }
                    else{
                        char val[30];
                        sprintf(val,"%.*f", 4, tabla[i][j]);
                   

                        label = gtk_label_new (val);
                        gtk_widget_set_size_request(label, 700/(mitadJuegos + 2), 700/(mitadJuegos+ 2));

                         box = gtk_box_new(0, 0);
                        gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                        const GdkRGBA *color;
                        
                        gdk_color_parse( "#A9D0F5", &color );
                        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &color);
                        gtk_grid_attach(GTK_GRID(grid2), box, j+1, i+1, 1, 1);

                        gtk_widget_show (label);
                        gtk_widget_show (box);   
                    }
                }
            }
        }
    }

    gtk_container_add (GTK_CONTAINER (tabla_sol_SD), grid2);
    gtk_widget_show (grid2);   
    
}

void on_scaleCasa_value_changed()
{
    //gtk_range_get_value(scaleCasa);
    ph = gtk_range_get_value(GTK_RANGE(scaleCasa));
    calcular();
    //g_print("%f", ph);
}

void on_scaleVisita_value_changed()
{
    pr = gtk_range_get_value(GTK_RANGE(scaleVisita));
    calcular();
    //g_print("%f", pr);
}



int on_btn_calcular_SD_clicked()
{   
    if(ph==0 && pr==0){
        gtk_label_set_text(GTK_LABEL(result), "Las dos probabilidades no pueden ser cero");
        return 0;
    }
    for(int i = 0; i < totalJuegos;i++){
        if(lugar_juego[i]==0){
            gtk_label_set_text(GTK_LABEL(result), "No se ha definido la ubicacion de todos los partidos");
            return 0;
        }
    }
   

	tabla = createFloatMatrix(mitadJuegos, mitadJuegos);


    for (int i=0;i<mitadJuegos;i++){
        for( int j = 0;j<mitadJuegos;j++){
            if(j==0){
                tabla[i][j]=0;
                continue;
            }
            if(i==0){
                tabla[i][j]=1;
                continue;
            }
            if(lugar_juego[totalJuegos-1-(i+j-2)] == 1){
                tabla[i][j]=ph*tabla[i-1][j]+qr*tabla[i][j-1];}

            if(lugar_juego[totalJuegos-1-(i+j-2)] == 2){
                tabla[i][j]=pr*tabla[i-1][j]+qh*tabla[i][j-1];
            }
            
       
        }

    }

    char val[120];
    strcpy(val,"La probabilidad de que A gane la serie es de: ");
    char v[30];
    sprintf(v,"%f",tabla[mitadJuegos-1][mitadJuegos-1]);
    strcat(val,v);

   	CrearTabla();


 
   
    gtk_label_set_text(GTK_LABEL(result), val);
}


void f_guardar(char* filename)
{

    FILE *file;
    file = fopen(filename, "w");
    
  

    fprintf(file, "%i\n", mitadJuegos);
    fprintf(file, "%i\n", totalJuegos);
    fprintf(file, "%f\n", ph);
    fprintf(file, "%f\n", pr);
    fprintf(file, "%f\n", qh);
    fprintf(file, "%f\n", qr);
    
    for (int i = 0 ;i < totalJuegos;i++){
        fprintf(file, "%i\n", lugar_juego[i]);
    }

    fclose(file);
}



void abrir(char* filename)
{    
 

    FILE *file;
    file = fopen(filename, "r");
    
    fscanf(file, "%i", &mitadJuegos);
    fscanf(file, "%i", &totalJuegos);
    fscanf(file, "%f", &ph);
    fscanf(file, "%f", &pr);
    fscanf(file, "%f", &qh);
    fscanf(file, "%f", &qr);
    
    

    int i = 0;

    while (i < totalJuegos)
    {
        fscanf(file, "%i", &lugar_juego[i]);
        i++;
    }

    fclose(file);

    
    if(totalJuegos==3){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C3), TRUE);
    }
    if(totalJuegos==5){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C5), TRUE);
    }
    if(totalJuegos==7){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C7), TRUE);
    }
    if(totalJuegos==9){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C9), TRUE);
    }
    if(totalJuegos==11){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(C11), TRUE);
    }

    actualizarIdaVuelta();

    char array[10];

    int pht = ph*10000;
    int prt = pr*10000;
   

    //snprintf(array, sizeof(array), "0.%d", pht);
    gtk_range_set_value(GTK_RANGE(scaleCasa), ph);
    gtk_range_set_value(GTK_RANGE(scaleVisita), pr);
    //gtk_entry_set_text(GTK_ENTRY(g_Ph),array);

    //snprintf(array, sizeof(array), "0.%d", prt);
    //gtk_entry_set_text(GTK_ENTRY(g_Pr),array);

    char val[40];
    strcpy(val,"Ph = ");
    char v[12];
    sprintf(v,"%f",ph);
    strcat(val,v);

    strcat(val,"\n");

    strcat(val,"Pr = ");
    char v1[12];
    sprintf(v1,"%f",pr);

    strcat(val,v1);

    gtk_label_set_text(GTK_LABEL(probabilidades1), val);

    strcpy(val,"Qh = ");
    char v2[12];
    sprintf(v2,"%f",qh);
    strcat(val,v2); 

    strcat(val,"\n");

    strcat(val,"Qr = ");
    char v3[8];
    sprintf(v3,"%f",qr);
    strcat(val,v3);    

    gtk_label_set_text(GTK_LABEL(probabilidades2), val);

}

void actualizarIdaVuelta()
{
    if(lugar_juego[0] == 1){
        gtk_button_set_image (GTK_BUTTON (A1), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B1), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[0] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A1), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B1), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[1] == 1){
        gtk_button_set_image (GTK_BUTTON (A2), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B2), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[1] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A2), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B1), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[2] == 1){
        gtk_button_set_image (GTK_BUTTON (A3), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B3), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[2] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A3), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B3), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[3] == 1){
        gtk_button_set_image (GTK_BUTTON (A4), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B4), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[3] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A4), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B4), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[4] == 1){
        gtk_button_set_image (GTK_BUTTON (A5), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B5), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[4] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A5), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B5), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[5] == 1){
        gtk_button_set_image (GTK_BUTTON (A6), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B6), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[5] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A6), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B6), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[6] == 1){
        gtk_button_set_image (GTK_BUTTON (A7), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B7), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[6] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A7), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B7), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[7] == 1){
        gtk_button_set_image (GTK_BUTTON (A8), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B8), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[7] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A8), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B8), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[8] == 1){
        gtk_button_set_image (GTK_BUTTON (A9), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B9), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[8] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A9), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B9), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[9] == 1){
        gtk_button_set_image (GTK_BUTTON (A10), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B10), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[9] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A10), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B10), gtk_image_new_from_file ("glade/Verde.png"));
    }

    if(lugar_juego[10] == 1){
        gtk_button_set_image (GTK_BUTTON (A11), gtk_image_new_from_file ("glade/Verde.png"));
        gtk_button_set_image (GTK_BUTTON (B11), gtk_image_new_from_file ("glade/Rojo.png"));
    }
    else
        if(lugar_juego[10] == 2)
    {
        gtk_button_set_image (GTK_BUTTON (A11), gtk_image_new_from_file ("glade/Rojo.png"));
        gtk_button_set_image (GTK_BUTTON (B11), gtk_image_new_from_file ("glade/Verde.png"));
    }

}

float stof(const char* s){
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



int calcular(){

    qr = 1 - ph;
    qh = 1 - pr;
    char val[40];
    strcpy(val,"Ph = ");
    char v[12];
    sprintf(v,"%f",ph);
    strcat(val,v);

    strcat(val,"\n");

    strcat(val,"Pr = ");
    char v1[12];
    sprintf(v1,"%f",pr);

    strcat(val,v1);

    gtk_label_set_text(GTK_LABEL(probabilidades1), val);

    strcpy(val,"Qh = ");
    char v2[12];
    sprintf(v2,"%f",qh);
    strcat(val,v2); 

    strcat(val,"\n");

    strcat(val,"Qr = ");
    char v3[8];
    sprintf(v3,"%f",qr);
    strcat(val,v3);    

    gtk_label_set_text(GTK_LABEL(probabilidades2), val);

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
        f_guardar(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    }
    gtk_widget_destroy(dialog);

}