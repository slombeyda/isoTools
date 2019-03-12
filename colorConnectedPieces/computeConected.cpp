#include <stdlib.h>
#include <stdio.h>

int *components;
int ncomponents=0;
int componentssize=0;

int currentComponent=0;
void setup() {
  componentssize=12437;
  components=(int *)malloc(sizeof(int)*componentssize);
  for (int i=0; i<componentssize; i++)
   components[i]=-1;
}

int  reconnectAs(int dst,int src) {
   for (int i=0; i<componentssize; i++)
      if (components[i]==dst) components[i]=src;
   return src;
}

int connect(int vertex, int component) {
   if (components[vertex]<0) {
      components[vertex]=component;
      return component;
   }
   if (components[vertex]==component)
      return component;
   if (components[vertex]<component)
      return reconnectAs(component,components[vertex]);
   return reconnectAs(components[vertex],component);
}

int maxcomponent=0;
void process() {
  int p0,p1,p2;
  while (scanf("%i %i %i",&p0,&p1,&p2)==3) {
     int c=currentComponent;
     c=connect(p0,c);
     c=connect(p1,c);
     c=connect(p2,c);
     if (c>maxcomponent) maxcomponent=c;
     if (c==currentComponent) currentComponent++;
  }
}

void packcomponents() {
   int c=0;
   for (int n=0; n<=maxcomponent; n++) {
      bool inuse=false;
      for (int i=0; i<componentssize && !inuse; i++) inuse=(components[i]==n);
      if (inuse) {
        for (int i=0; i<componentssize; i++) {
           if (components[i]==n) components[i]=c;
        }
        c++;
      }
   }
}

void finalize() {
  for (int i=0; i<componentssize; i++) 
     printf("%i\n",components[i]);
}

int main() {
   setup();
   process();
   packcomponents();
   finalize();
}
