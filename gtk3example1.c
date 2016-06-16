#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct _EventData {
    int control;
} EventData;

EventData *eventData1 = NULL;
EventData *eventData2 = NULL;      

static void
startup (GtkApplication* app)
{
    g_print ("startup()\n");
    eventData1 = g_new(EventData, 1);
    eventData2 = g_new(EventData, 1);      
    
}


void
print_hello (GtkWidget *widget,
             gpointer   data)
{
    EventData *eventData = (EventData *)data;
    if (eventData->control == 1) {
        g_print ("Hello World\n");
    }
    else if (eventData->control == 2) {
        g_print ("Do more\n");
    }

}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
    g_print ("activate()\n");
  GtkWidget *window;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);
  
  gtk_widget_show_all (window);

  button1 = gtk_button_new_with_label ("Hello World");
  eventData1->control = 1;
  g_signal_connect (button1, "clicked", G_CALLBACK (print_hello), eventData1);
  gtk_container_add (GTK_CONTAINER (button_box), button1);

  button2 = gtk_button_new_with_label ("More useful");
  eventData2->control = 2;
  g_signal_connect (button2, "clicked", G_CALLBACK (print_hello), eventData2);
  gtk_container_add (GTK_CONTAINER (button_box), button2);
  

  /* g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window); */
  
  gtk_widget_show_all (window);
}

static void
shutdown (GtkApplication* app)
{
    g_print ("shutdown()\n");
    g_free(eventData1);
    g_free(eventData2);
    
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  g_signal_connect (app, "startup", G_CALLBACK (startup), NULL);
  g_signal_connect (app, "shutdown", G_CALLBACK (shutdown), NULL);
  g_print ("Heading into g_application_run()\n");
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_print ("Leaving g_application_run()\n");
  g_object_unref (app);

  return status;
}


