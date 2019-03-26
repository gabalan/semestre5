// Pour utiliser les bibliothèques standards
import java.util.Random;
import java.util.Scanner;

class Mystere {

	// Permet de lire ce que l'utilisateur saisi au clavier
	public static Scanner clavier = new Scanner(System.in);

	public static void main(String[] args) {
		// Un générateur de nombre aléatoire
		Random aleatoire = new Random();
		// Génère un nombre compris entreo 0 et 100 (exclus)
		int mystere = aleatoire.nextInt(100);

		System.out.print("Nombre : ");
		// Lit un entier au clavier, génère une erreur si la valeur saisie n'est pas un entier
		int essai = clavier.nextInt();

		System.out.println("Votre nombre est " + essai + " et le nombre mystere est " + mystere);
	}
}
