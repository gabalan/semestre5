package Point2D;


import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.Point2D;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Random;

public class Planet extends Item{
	private int numberSpaceShip;
    private static transient Color saveLast =null  ;
    private Color player;
    private static int timeGenerate = 0;
    public static transient Planet  firstGame = null;
    private int nb;

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
    public String toStringnb() {
    	return ""+nb;
    }

    public Planet(double x, double y, int w,int nb) {
		super(x, y, w);
		this.nb=nb;
    }

    public Planet(double x, double y, int w,int nb, Color player) {
        super(x, y, w);
        this.player = player;
        this.nb=nb;
    }

   
    
    
}