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

 
int nSeconds = 0;                 
gint timer = 0;
int bTimerRunning = FALSE;

/* Determines if to continue the timer or not */
static gboolean continue_timer = FALSE;

/* Determines if the timer has started */
static gboolean start_timer = FALSE;

/* Display seconds expired */
static int sec_expired = 0;

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

GtkWidget *label;
///
GtkWidget *image;

/*
void hello_word_func(int signum)
{
    g_print ("Hello World!\n");
    signal (SIGALRM, hello_word_func);
    alarm (3);
}
*/

/*
pthread_t thread0;
void *OneMinuteCall(void *arg)
{
    g_print ("Hello\n");
    while(1)
    {
        
        system("dot -Tpng grafo.dot -o grafo.png");
        gtk_image_set_from_file (image, "grafo.png");
        g_print ("Hello World!\n");
        sleep(1);
    }
    return 0;
}*/

int TimerCallback (gpointer data)
{
    /* --- Another second has gone by --- */
    nSeconds++;
    system("dot -Tpng grafo.dot -o grafo.png");
    gtk_image_set_from_file (image, "grafo.png");
    return 1; // NOTE: Needs to be non-zero otherwise timer seems to be stopped.
}
/*
 * StartTimer
 *
 * Starts up the time.  Happens when the user first
 * clicks on a button.
 */
void StartTimer ()
{

    /* --- If the timer isn't already running --- */
    if (!bTimerRunning) {

        /* --- Start at zero --- */
        nSeconds = 0;

        /* --- Call function 'TimerCallback' every 1000ms --- */
        timer = g_timeout_add (1000, TimerCallback, NULL);

        /* --- Timer is running. --- */
        bTimerRunning = TRUE;
    }
}
///

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


///
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

//
    image = GTK_WIDGET(gtk_builder_get_object(builder, "ImgP3"));
//
    btn_Salir = GTK_WIDGET(gtk_builder_get_object(builder, "btnSalir"));
    btn_AcercaDe = GTK_WIDGET(gtk_builder_get_object(builder, "btnAcerca"));

	gtk_widget_set_tooltip_text(P1, "Inicia el programa del algoritmo Floyd-Warshall, el cual encuentra la ruta más corta para llegar de un punto a otro en grafos dirigidos ponderados.");
    gtk_widget_set_tooltip_text(P2, "Inicia el programa del algoritmo Knapsack problem, el cual busca encontrar la mejor solución con un conjunto de posibilidades a las cuales tienen un valor y un costo(peso), existe una 'mochila' con capacidad conocida para transportar los objetos, por lo que se debe maximizar la ganancia sin exceder el límite.");
    gtk_widget_set_tooltip_text(P3, "TBA");
    gtk_widget_set_tooltip_text(P4, "TBA");
    gtk_widget_set_tooltip_text(P5, "TBA");
    gtk_widget_set_tooltip_text(P6, "Termina el programa");
 	
 	gtk_widget_set_tooltip_text(btn_Salir, "Termina el programa");
    gtk_widget_set_tooltip_text(btn_AcercaDe, "Muestra información del programa y los miembros del equipo");
   


  
    g_object_unref(builder);
 
    gtk_widget_show(window); 



    g_timeout_add_seconds(1, _label_update, image);
    continue_timer = TRUE;
    start_timer = TRUE;

    gtk_main();
/*
    pthread_create(&thread0, NULL, OneMinuteCall, NULL);
 
    pthread_t tid;
    pthread_create(&tid, NULL, &threadproc, NULL);
   
    signal (SIGALRM, hello_word_func);
    alarm (3);
*/
    exit(3);
    return 0;
}




void on_btnP1Comenzar_clicked()
{
    system("./Rutas_Optimas &");
}

void on_btnP2Comenzar_clicked()
{
    system("./Pending &");
}

void on_btnP3Comenzar_clicked()
{

    
    system("dot -Tpng grafo.dot -o grafo.png");
    gtk_image_set_from_file (image, "grafo.png");

    
    
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

void terminar() {
    gtk_main_quit();
}

