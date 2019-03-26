package alien;

import java.util.ArrayList;
import java.util.Random;

import javafx.geometry.Point2D;
import javafx.geometry.*;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;



public  class Planet extends Item{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int numberSpaceShip;
    private static transient Color saveLast =null  ;
    private Color player;
    private static int timeGenerate = 0;
    public static transient Planet  firstGame = null;

    //System.identityHashCode(this); give me uniq id of my object

    /**
     * allows to have the color of the player (of the planet)
     * @return color of planet
     */
    public Color getPlayer() {
        return player;
    }

    /**
     * allows to have time for the generation of new planet
     * @return int  time
     */
    public static int getTimeGenerate() {
        return timeGenerate;
    }

    public static void setTimeGenerate(int timeGenerate) {
        Planet.timeGenerate = timeGenerate;
    }

    public Planet(double x, double y, int w) {
		super(x, y, w);

        int color = randomColor();
        if(color==0)
        {
            this.player=Color.GREEN;
            saveLast=Color.GREEN;
        }
        else
        if(color==1)
        {
            this.player=Color.BLUE;
            saveLast=Color.BLUE;
        }

        else
        if(color==2)
        {
            this.player=Color.BLACK;
            saveLast=Color.BLACK;
        }


        if(!this.player.equals(Color.BLACK))
            this.numberSpaceShip=20;
        else
            this.numberSpaceShip=0;



    }

    public Planet(double x, double y, int w, Color player) {
        super(x, y, w);
        this.player = player;
    }

    /**
     * intelligently generate colors for planet or ship creation
     * @return int corresponding of color
     */
    private int randomColor()
	{
		//Number 0 GREED

		//Number 1 BLUE

		//Number 2 BLACK
		Random rand =new Random();
		if(saveLast==Color.GREEN)
        {
            return 1;
        }else
        if(saveLast==Color.BLUE)
            return 0;


		return rand.nextInt(3);

	}
    public void setObjective(Item item) {}

    public void move() {}

	public boolean contains(Point2D p) {

        return squareDistance(this.center, p) <= (getWidth() / 2) * (getWidth() / 2);

	}

    /**
     * allows to increment the number of ships when timeGenerate would have a value greater than or equal to 10000 ms
     */
	public static void UpdateUniteAfterTime()
    {
        if (Planet.getTimeGenerate()>=10000) {
            for (Item item : Item.collection) {

                if (item instanceof Planet && !((Planet) item).getPlayer().equals(Color.BLACK)) {
                    ((Planet) item).numberSpaceShip += 1;

                }
            }
            Planet.setTimeGenerate(0);
        }

    }

    /**
     *allows you to create ships
     * @param item the collection containing all the items (planets and ships)
     * @param objectif of SpaceShip
     * @param nbescadron is the number of ships to send to the target planet
     */
	public void createSpaceShip(ArrayList<Item> item, Item objectif, int nbescadron)
    {
        Random random = new Random();
        int x,y;
        SpaceShip spaceShip;

        for (int i = 0; i <nbescadron ; i++) {
        	x=random.nextInt(gettwidth()-30);
            y=random.nextInt(gettwidth()-30);
            while ((x==this.getLocation().getX() &&  y==this.getLocation().getY() ) ||
                    squareDistance(this.getLocation(),new Point2D(x,y))>2500 ||
                    this.contains(new Point2D(x,y)))
            {
                x=random.nextInt(gettwidth()-30);
                y=random.nextInt(gettwidth()-30);
            }
            spaceShip = new SpaceShip(x,y, this.getWidth()/4,this.player,System.identityHashCode(this));
            spaceShip.setObjective(objectif);
            Item.collection.add(spaceShip);
            item.add(spaceShip);
        }
        this.numberSpaceShip= this.numberSpaceShip-nbescadron;

    }

    public int getNumberSpaceShip() {
        return numberSpaceShip;
    }

    @Override
    public String toString() {
        return "Planet Code:"+System.identityHashCode(this)+"  " +toStringColor(this.player)+" nbSpaceShip: "+this.numberSpaceShip;
    }

    /**
     *can attack a planet if it does not have an attack in court or it just changes the goal
     * @param objectiv cible of planet
     * @param action allows to determine according to CRTL - ALT -SHIF the number of ships to send
     */

    public void setNumberSpaceShip(int numberSpaceShip) {
        this.numberSpaceShip = numberSpaceShip;
    }

    /**
     * allows you to return a list of ships belonging to a given planet in parameter using System.identityHashCode of the planet
     * @param who la planete concernée
     * @return list of SpaceShip
     */
    public ArrayList<Item> mySpaceShips(Item who)
    {
        ArrayList<Item> spaceShips = new ArrayList<>();
        for (Item item: Item.collection) {
            if (item instanceof SpaceShip && ((SpaceShip) item).getIDPlanet()==System.identityHashCode(who))
                spaceShips.add(item);
        }
        return spaceShips;
    }


    /**
     * allows to evaluate the damage or the troop movements to carry out by increasing or decreasing the number of ships of the planets concerned
     * @param objectiv of SpaceShip
     * @param power of SpaceShip
     * @return true or false after evaluate
     */
    public   boolean afterAttak(Item objectiv, int power)
    {


        Planet destination = (Planet)objectiv;
        ArrayList<Item> myspaceShips = mySpaceShips(destination);
        if(!this.player.equals(Color.BLACK) && this.getPlayer().equals(destination.getPlayer()))
        {
            destination.setNumberSpaceShip(destination.getNumberSpaceShip()+1);
            return true;

        }
        else if(destination.getPlayer().equals(Color.BLACK) || (!destination.getPlayer().equals(Color.BLACK) && destination.numberSpaceShip<=0))
        {
            destination.numberSpaceShip = numberSpaceShip;

            destination.player = this.getPlayer();

            if(!myspaceShips.isEmpty())
            {
                for (int i = 0; i <myspaceShips.size() ; i++) {
                    SpaceShip sship = (SpaceShip) myspaceShips.get(i);
                    sship.setColor(this.player);
                }
            }
            return true;

        }
        else
        {
            if(!Color.BLACK.equals(player))
            {
                destination.setNumberSpaceShip(destination.getNumberSpaceShip()-power);
                if(destination.numberSpaceShip<=0)
                {
                    destination.player = this.getPlayer();

                    if(!myspaceShips.isEmpty())
                    {
                        for (int i = 0; i <myspaceShips.size() ; i++) {
                            SpaceShip sship = (SpaceShip) myspaceShips.get(i);
                            sship.setColor(this.player);
                        }
                    }
                }
                return true;
            }


        }
        return false;


    }

    /**
     *allows to compare two planets based on the method of the parent class
     * @param o
     * @return true if it's the same else false
     */
    @Override
    public boolean equals(Object o) {
        if(o==null)
            return false;
        if(this==o)
            return true;
        if(o instanceof Planet)
        {
            if(this.player.equals(((Planet) o).player) && this.numberSpaceShip==((Planet) o).numberSpaceShip && super.equals(o))
                return true;
        }
        return false;
    }

	@Override
	public void draw(GraphicsContext arg0) {
		// TODO Auto-generated method stub
		
	}
}
