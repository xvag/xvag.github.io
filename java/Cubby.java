import static java.lang.System.*;
import java.math.*;

class Producer extends Thread {
	private CubbyHole cubbyhole;
	private int number;
	
	public Producer(CubbyHole c, int number) {
		cubbyhole = c;
		this.number = number;
	}
	
	public void run() {
		for (int i=0; i<9; i++) {
			cubbyhole.put(i);
			out.println("Producer #"+this.number+" put:"+i);
			try {
				sleep((int)(Math.random()*1000));
			} catch (InterruptedException e) {}
		}
	}
}

class Consumer extends Thread {
	private CubbyHole cubbyhole;
	private int number;
	
	public Consumer(CubbyHole c, int number) {
		cubbyhole = c;
		this.number = number;
	}
	
	public void run() {
		int value = 0;
		for (int i=0; i<9; i++) {
			value = cubbyhole.get();
			out.println("Consumer #"+this.number+" got:"+value);
		}
	}
}

class CubbyHole {
	private int contents;
	private boolean available = false;
	
	public synchronized int get() {
		while (available == false) {
			try {
				wait();
			} catch (InterruptedException e) {}
		}
		available = false;
		out.println("in get");
		notifyAll();
		return contents;
	}
	
	public synchronized void put (int value) {
		while (available == true) {
			try {
				wait();
			} catch (InterruptedException e) {}
		}
		contents = value;
		available = true;
		out.println("in put");
		notifyAll();
	}
}

public class Cubby {
	public static void main(String[] args) {
		CubbyHole c = new CubbyHole();
		Producer p1 = new Producer(c, 1);
		Consumer c1 = new Consumer(c, 1);
		
		p1.start();
		c1.start();
	}
}