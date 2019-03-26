package alien;



import java.io.Serializable;
import java.util.ArrayList;
import java.util.Random;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.paint.Color;

/**
 * Any graphical element that will be handle by the application.
 *
 */
abstract class Item extends Game implements Serializable  {

	protected final Point2D center;
	private final int width;
    /**
     * a collection containing all the planets and ships of the game
     */
	public static transient ArrayList<Item> collection ;

	public Item(double x, double y, int w) {
		center = new Point2D(x, y);
		width = w;
	}

	public Point2D getLocation() {
		return center;
	}

	public int getWidth() {
		return width;
	}


	public abstract void move();

    /**
     *this synchronized method allows the user to play himself with his opponent as parameter
     * @param player
     */
    public abstract void draw(GraphicsContext arg0);

	/*
	 * Idem
	 */
	public abstract void setObjective(Item o);



	public abstract boolean contains(Point2D p);

    /**
     *converts our colors used into strings of characters
     * @param color
     * @return the string corresponding to the color (BLUE - GREEN - BLACK)
     */
	public static String toStringColor(Color color)
	{

		if (Color.BLACK.equals(color))
			return "BLACK";
		if (Color.GREEN.equals(color))
			return "GREEN";
		if(Color.BLUE.equals(color))
			return "BLUE";
		return String.valueOf(color);
	}

    /**
     *Calculate the radius of cirlce
     * @return
     */
	public double getRayon()
	{
		return Math.sqrt(Math.pow(getWidth(),2) + Math.pow(getWidth(),2)  ) /2;
	}

    /**
     * Used to compare two Items based on these coordinates and its width
     * @param o
     * @return true ou false
     */
	@Override
	public boolean equals(Object o) {
		if (o==null)
			return false;
		if(o==this)
			return true;
		if(o instanceof Item)
		{
			if (this.center.equals(((Item) o).center) && this.width==((Item) o).width)
				return true;
		}
		return false;
	}

    protected static int squareDistance(Point2D p1, Point2D p2) {

        double dx = p1.getX() - p2.getX();
        double dy = p1.getY() - p2.getY();
        return (int) (dx * dx + dy * dy);

    }

    /**
     * allows you to remove ships that have reached their target
     */
    public static void eraseAfterAttak()
    {
        for (int i = 0; i <Item.collection.size() ; i++) {
            if(Item.collection.get(i) instanceof SpaceShip && ((SpaceShip) Item.collection.get(i)).getObjective().contains(Item.collection.get(i).center))
                Item.collection.remove(i);
        }
    }

    /**
     * allows to determine the end of the game
     * @return Color.RED if one is at the end otherwise return the color of the winning player
     */
   
    /**
     * Allows you to create a list of planets of all colors
     * @param number of planet to create
     * @return list of planet
     */
	public static ArrayList<Item>  createPlanet(int number )
    {
        if (number<=5)
            number=10;
        int x, y;
        ArrayList<Item> testItemList = new ArrayList<>();
        Random random = new Random();
        for (int i = 0; i < number; i++) {
        	x=random.nextInt(gettwidth()-30);
            y=random.nextInt(gettwidth()-30);
            if (!testItemList.isEmpty()) {

                for (int j = 0; j < testItemList.size(); j++) {

                    while ((x == testItemList.get(j).getLocation().getX() && y== testItemList.get(j).getLocation().getY()) ||
                            testItemList.get(j).contains(new Point2D(x-30, y-30)) ||
                            testItemList.get(j).contains(new Point2D(x+30, y+30)) ||
                            testItemList.get(j).contains(new Point2D(x-30, y+30)) ||
                            testItemList.get(j).contains(new Point2D(x+30, y-30)) ||
                            testItemList.get(j).contains(new Point2D(x, y)) ||
                            x<=30 || y<=20 ) {
                    	x=random.nextInt(gettwidth()-30);
                        y=random.nextInt(gettwidth()-30);

                    }

                }
            }

            testItemList.add(new Planet(x, y, 60));

        }
        return testItemList;
    }

    /**
     *create a neutral planet list and add them to Item.collection
     */
    public  static  void createPlanetBlack()
    {
        int x, y;

        Random random = new Random();
        for (int i = 0; i < 4; i++) {
            x = random.nextInt(750);
            y = random.nextInt(850);
            if (!Item.collection.isEmpty()) {

                for (int j = 0; j < Item.collection.size(); j++) {

                    while ((x == Item.collection.get(j).getLocation().getX() && y== Item.collection.get(j).getLocation().getY()) ||
                            Item.collection.get(j).contains(new Point2D(x-30, y-30)) ||
                            Item.collection.get(j).contains(new Point2D(x+30, y+30)) ||
                            Item.collection.get(j).contains(new Point2D(x-30, y+30)) ||
                            Item.collection.get(j).contains(new Point2D(x+30, y-30)) ||
                            Item.collection.get(j).contains(new Point2D(x, y)) ||
                            x<=30 || y<=20 ) {
                        x = random.nextInt(750);
                        y = random.nextInt(850);

                    }

                }
            }

            Item.collection.add(new Planet(x, y, 60,Color.BLACK));

        }
    }
}