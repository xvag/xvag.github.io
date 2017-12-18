import static java.lang.System.*;

class Airplane {
	private static int totalSeats;
	private int capacity = 10;
	private static String[] Bookings = new String[100];
	
	public Airplane() {
		totalSeats = 0;
	}
	
	public int getSeat(String Bname) {
		if(totalSeats<capacity) {
			Bookings[totalSeats] = Bname;
			totalSeats++;
			return 1;
		} else {
			return 0;
		}
	}
	
	public int getTotalSeats() {
		return totalSeats;
	}
	
	public int getCapacity() {
		return capacity;
	}
	
	public void getBookings()
	{
		out.println("Bookings Records");
		out.println("Total seats booked = "+totalSeats);
		for(int i=0; i<totalSeats; i++)
		{
			out.println("Seat:"+i+" booked by "+Bookings[i]);
		}
	}
}



class BookingAgent implements Runnable {
	private Thread  agentThread;
	private Airplane airplane;
	private String Bname;
	private int myseats;
	
	public BookingAgent(String bname, Airplane p) {
		this.Bname = bname;
		airplane = p;
		myseats = 0;
	}
	
	public void start() {
		if(agentThread == null) {
			agentThread = new Thread(this, "Ticket");
			agentThread.start();
		}
	}
	
	public void stop() {
		agentThread = null;
	}
	
	public void run() {
		for (int k=0; k<10; k++) 
			getMySeat();
		//out.println(Bname+" myseats="+myseats);
	}	
	
	synchronized public void getMySeat() {
		if(airplane.getSeat(Bname)==1) {
			out.println("Agent("+Bname+"): I booked a seat");
			myseats+=1;
		}
		else
			out.println("Agent("+Bname+"): no more seats");
		try {
			Thread.sleep(50);
		} catch (InterruptedException e) {};
	}
	
	public void getMyBookings() {
		out.println("Agent("+Bname+"): I have booked "+myseats+" seats.");
	}
}



class Air {
	public static void main(String[] args) throws InterruptedException{
		Airplane park = new Airplane();
		BookingAgent t1 = new BookingAgent("T1",park);
		BookingAgent t2 = new BookingAgent("T2",park);
		BookingAgent t3 = new BookingAgent("T3", park);
		
		
		t1.start();
		t2.start();
		t3.start();
		
		Thread.sleep(1000);
		
		out.println();
		t1.getMyBookings();
		t2.getMyBookings();
		t3.getMyBookings();

		out.println();
		park.getBookings();
		
	}
}