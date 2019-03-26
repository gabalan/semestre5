package alien;

import java.io.Serializable;
import java.util.Random;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

class SpaceShip extends Item{

	private Item objective;
	private Color color;
	private int speed;
	private int timeProduction;
	private int power;
	private int IDPlanet ;


	public SpaceShip(double x, double y, int w, Color color,int IDPlanet) {
		super(x, y, w);
		objective = this;
		this.color=color;
		this.speed = 8;
		this.timeProduction = 5;
		setRandPower();
		this.IDPlanet= IDPlanet;
	}

	/**
	 * allows to randomly generate the power of a ship between 1 and 3 excluded
	 */
	public void setRandPower() {
		Random random = new Random();
		int power = random.nextInt(3);
		while(power==0)
		{
			power=random.nextInt(3);
		}
		this.power = power;
	}

	public int getPower() {
		return power;
	}

	public void setObjective(Item o) {
		this.objective = o;
	}


	@Override
	public boolean contains(Point2D p) {
        double w = getWidth() / 2;
        return (this.center.getX() - w <= p.getX() && p.getX() <= this.center.getX() + w)
                && (this.center.getY() - w <= p.getY() && p.getY() <= this.center.getY() + w);
	}

	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
		this.color = color;
	}

	public Item getObjective() {
		return objective;
	}

	/**
	 * to allow to move towards their target
	 */
	public void move() {
	}

	@Override
	public void draw(GraphicsContext arg0) {
		Point2D pos = this.center;
		int x = (int) pos.getX(), y = (int) pos.getY(), w = this.getWidth();
		arg0.setFill(this.color);
		arg0.fillRect(x - w / 2, y - w / 2, w, w);

	}

    public int getIDPlanet() {
        return IDPlanet;
    }

    @Override
	public String toString() {
		return "SpaceShip "+toStringColor(this.color)+" From "+this.IDPlanet;
	}

	/**
	 * avoids flying over the planets on your target planet
	 * @param x position actuel of spaceship
	 * @param y position actuel of spaceship
	 * @return return a new Point to dodge other planet
	 */



	/**
	 * allows to compare two vessels with their characteristics and compared to the equals of the parent class
	 * @param o
	 * @return true if it's the same else false
	 */
}