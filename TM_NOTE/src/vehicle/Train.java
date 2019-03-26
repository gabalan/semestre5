package vehicle;

import journey.City;

public class Train extends Vehicle{
	Train train;
	public Train(String name,int passengers,int speed,int kmcost) {
		super.name=name;
		super.passengers=passengers;
		super.speed=speed;
		super.kmcost=kmcost;
		
	}
	public Train(String name) {
		super.name=name;
	}
	public Train(Train name) {
		this.train=name;
	}

	public int nbJourneyPerDay(int distance) {
		float temps=distance/speed;
		return (int)(24/temps);
	}
	public boolean compatibleWith(City c) {
		if(c.getStation()==true) {
			return true;
		}
		return false;
	}
	public boolean equals(Object o) {
		if(o==null) {
			return false;
		}else {
			if(o instanceof Train) {
				Train t=(Train) o;
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