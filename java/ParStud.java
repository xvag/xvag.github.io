import static java.lang.System.*;

// Parent

class Parent extends Thread {
	private Account account;

	private double amount;
	
	public Parent(Account c) {
		account = c;
	}
	
	public void run() {
		for (int i=0; i<10; i++) {
			amount = Math.random()*1000;
			out.printf("Parent puts %5.2f\n\n",amount);
			account.put(amount);
			try {
				sleep((int)(Math.random()*1000));
			} catch (InterruptedException e) {}
		}
	}
}


// Student

class Student extends Thread {
	private Account account;
	private double amount;
	
	public Student(Account c) {
		account = c;
	}
	
	public void run() {
		for (int i=0; i<10; i++) {
			amount = Math.random()*500;
			out.printf("Student tries to get %5.2f\n\n",amount);
			amount = account.get(amount);
		}
	}
}


// The Account

class Account {
	private static double contents;
	private boolean available = false;
	
	public synchronized double get(double amount) {
		while (available == false) {			
			try {
				wait();
			} catch (InterruptedException e) {}
		}
		available = false;
		contents -= amount;
		out.printf("in get - Student got %5.2f - Contents=%8.2f\n",amount,contents);
		notifyAll();
		return amount;
	}
	
	public synchronized void put (double amount) {
		while (available == true) {
			try {
				wait();
			} catch (InterruptedException e) {}
		}
		available = true;
		contents += amount;
		out.printf("in put - Parent put %5.2f - Contents=%8.2f\n",amount,contents);
		notifyAll();
	}
	
	public double getContents() {
		return contents;
	}
}


// Main

public class ParStud {
	public static void main(String[] args) {
		Account acc = new Account();
		Parent p1 = new Parent(acc);
		Student s1 = new Student(acc);
		
		p1.start();
		s1.start();
	}
}