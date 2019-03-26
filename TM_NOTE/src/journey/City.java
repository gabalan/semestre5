package journey;

public class City{
	private String name;
	private boolean station;
	public City(String name,boolean station) {
		this.name=name;
		this.station=station;
	}
	
	public String getName() {
		return name;
	}
	public boolean getStation() {
		return station;
	}
	public void setStation(boolean station) {
		this.station=station;
	}
	public void setName(String name) {
		this.name=name;
	}
}