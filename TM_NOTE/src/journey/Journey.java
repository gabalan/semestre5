package journey;

import vehicle.Vehicle;

public class Journey{
	private City city1,city2;
	int distance;
	int passengerTicket;
	Vehicle[] vehicles=new Vehicle[100]; 
	Journey[] journeys = new Journey[100];
	int nbVehicle;
	public Journey(City city1,City city2,int distance,int passengerTicket) {
		this.city1=city1;
		this.city2=city2;
		this.distance=distance;
		this.passengerTicket=passengerTicket;
		this.nbVehicle=0;
	}
	
	public City getcity1() {
		return city1;
	}
	public City getcity2() {
		return city2;
	}
	public int getDistance() {
		return distance;
	}
	public Vehicle[]  getVehicles() {
		return vehicles;
	}
	public void setCity1(City city) {
		city1=city;
	}
	public void setCity2(City city) {
		city2=city;
	}
	public void setDistance(int dis) {
		distance=dis;
	}
	public boolean addVehicle(Vehicle vehicle) {
		if(vehicle.compatibleWith(city1.getName())==true && vehicle.compatibleWith(city2.getName())==true ) {
			this.vehicles[nbVehicle]=vehicle;
			nbVehicle+=1;
			return true;
			
		}
		return false;
	}
	
	public int nbJourneyPerDay(int distance) {
		float temps=distance/vehicles[0].getSpeed();
		return (int)(24/temps);
	}
	public int passengersPerDay() {
		int total = 0;
		for(int i=0; i<nbVehicle; i++) {
			total += vehicles[i].getPassengers() * vehicles[i].nbJourneyPerDay(distance);
		}
		return total;
	}

	public boolean contains(Vehicle myVehicle) {
		for(int i=0; i<nbVehicle; i++) {
			if(vehicles[i].equals(myVehicle)) {
				return true;
			}
		}
		return false;
	}
	public int costPerDay() {
		int total = 0;
		for(int i=0; i<nbVehicle; i++) {
			total += vehicles[i].getKmCost() * distance * vehicles[i].nbJourneyPerDay(distance);
		}
		return total;
	}
	
	
	public int incomePerDay() {
		return this.passengersPerDay() * passengerTicket;
	}
	
	public int benefitPerDay() {
		return this.incomePerDay() - this.costPerDay();
	}

	public String toString() {
		return city1 + "-" + city2;
	}	

}
