package vehicle;

import journey.City;

public abstract  class Vehicle{
	protected  String name;
	protected int passengers;
	protected int speed;
	protected int kmcost;
	
	public String getName() {
		return name;
	}
	public int getPassengers() {
		return passengers;
	}
	public int getSpeed() {
		return speed;
	}
	public int getKmCost() {
		return kmcost;
	}
	public void setName(String name) {
		this.name=name;
		}
	public void setPassengers(int pass) {
		passengers=pass;
	}
	public void setSpeed(int speed) {
		this.speed=speed;
		}
	public void setKmcost(int kmcost) {
		this.kmcost=kmcost;
	}
	public String toString() {
		return "Vehicle name "+name+" nb_passengers "+passengers+" ,speed" +this.speed+ " kmcost "+this.kmcost;   
	}
	 public int nbJourneyPerDay(int distance) {
		
		return 0;
	}
	public boolean compatibleWith(String name2) {
		// TODO Auto-generated method stub
		return false;
	}
	
}