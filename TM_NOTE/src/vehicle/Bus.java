package vehicle;

import journey.City;

public class Bus extends Vehicle{
	public Bus bus;
	public Bus(String name,int passengers,int speed,int kmcost) {
		super.name=name;
		super.passengers=passengers;
		super.speed=speed;
		super.kmcost=kmcost;
		
	}
	public Bus(String bus) {
		this.name=bus;
	}
	public Bus(Bus name) {
		this.bus=name;
	}
	public String toString() {
		return "Vehicle name "+name+" nb_passengers "+passengers+" ,speed" +this.speed+ " kmcost "+this.kmcost;   
	}
	
	public int nbJourneyPerDay(int distance) {
		float temps=distance/speed;
		return (int)(24/temps);
	}
	public boolean compatibleWith(City c) {
		return true;
	}
	public boolean equals(Object o) {
		if(o==null) {
			return false;
		}else {
			if(o instanceof Bus) {
				Bus t=(Bus) o;
				if(t.name==this.name && t.passengers==this.passengers && t.speed==this.speed && t.kmcost==this.kmcost ) {
					return true;
				}
				else {
					return false;
				}
			}
			return false;
		}
	}
}