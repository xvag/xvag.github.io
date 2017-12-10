import static java.lang.System.*;

class Airplane {
	private static int totalSeats;
	private static int capacity = 10;
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
		out.println("total seats booked = "+totalSeats);
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
		try {
		for (int k=0; k<10; k++) { //while(airplane.getTotalSeats()<airplane.getCapacity()) {
			if(airplane.getSeat(Bname)==1) {
				myseats += 1;}			
			//	out.println("Agent("+Bname+") total seats: "+airplane.getTotalSeats());
			//else 
			//	out.println("Agent("+Bname+") no more seats");
			Thread.sleep(50);
		}
		} catch (InterruptedException e) {
			out.println("Agent("+Bname+") interrupted");
		}
		out.println(Bname+" myseats="+myseats);
	}
}

class Air {
	public static void main(String[] args) {
		Airplane park = new Airplane();
		BookingAgent t1 = new BookingAgent("T1",park);
		BookingAgent t2 = new BookingAgent("T2",park);
		BookingAgent t3 = new BookingAgent("T3", park);
		
		
		t1.start();
		//t2.start();
		//t3.start();
		
		park.getBookings();
		
	}
}