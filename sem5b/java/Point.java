// Pour utiliser les bibliothèques standards
import java.util.Random;
import java.util.Scanner;


class Point{
  double x;//abscisse
  double y; //ordonnée

void afficher(){
    System.out.println("les cordonnéés sont:");
    System.out.println("abscisse="+x+" ordonnée="+y);
  }
  // Deplace un point par rapport à sa position d'origine
void deplacement(double dx, double dy){
  x=x+dx;
  y=y+dy;
}
void deplacement(double delta){

  x=x+delta;
  y=y+delta;
} // meme deplacement en x et en y
//LES ACCESSEURS
double getx(){
  return x;
}
double gety(){
  return y;
}
// Calcul la distance entre deux points
double distance(Point p){
  return Math.sqrt(Math.pow((getx()-p.x),2)+Math.pow((gety-p.y),2));

}
}
