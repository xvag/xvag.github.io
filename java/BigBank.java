import static java.lang.System.*;

interface Banking {
	void deposit(int amount);
	void withdraw(int amount);
	int remain();
}

abstract class BankAccount implements Banking{
	
	private String name;
	private int afm;
	private int amount;
	
	public BankAccount(String name, int afm, int amount)
	{
		this.name = name;
		this.afm = afm;
		this.amount = amount;
	}
	
	public void deposit(int amount)
	{
		this.amount+=amount;
		out.println("Account balance after deposit: "+this.amount);
	}
	
	public void withdraw(int amount)
	{
		this.amount-=amount;
	}
	
	public int remain()
	{
		return this.amount;
	}
	
	public String getInfo()
	{
		String info = name+' '+afm+' '+amount;
		return info;
	}

}

class Regular extends BankAccount
{
	public Regular(String n, int a, int am)
	{
		super(n,a,am);
	}
	
	public void withdraw(int amount)
	{
		int rem=super.remain();
		if (rem>=amount)
			super.withdraw(amount);
		else
			out.println("Not enough money");
		out.println("Account balance after withdraw: "+super.remain());
	}
}

class Overdraft extends BankAccount
{
	public Overdraft(String n, int a, int am)
	{
		super(n,a,am);
	}
	
	public void withdraw(int amount)
	{
		int rem=super.remain();
		if (rem+500>=amount)
			super.withdraw(amount);
		else
			out.println("Not enough money");
		out.println("Account balance after withdraw: "+super.remain());
	}
}

class Checking extends BankAccount
{
	public Checking(String n, int a, int am)
	{
		super(n,a,am);
	}
	
	public void deposit(int amount)
	{
		amount -= 1;  
		super.deposit(amount);
	}
	
	public void withdraw(int amount)
	{
		amount += 1; //ok profanws me mia diadikasia to amount 8a vgei se xartonomismata apo to atm kai to 1 8a paei stin trapeza
		int rem=super.remain();
		if (rem>=amount)
			super.withdraw(amount);
		else
			out.println("Not enough money");
		out.println("Account balance after withdraw: "+super.remain());
	}
}

public class BigBank {
	public static void main(String[] args)
	{
		BankAccount xacc, yacc, zacc;
		
		xacc = new Regular("xname",1458,10000);
		out.println("Info: "+ xacc.getInfo());
		xacc.deposit(100);
		xacc.withdraw(1000);
		xacc.withdraw(10000);
		
		yacc = new Overdraft("yname",1558,1000);
		out.println("Info: "+ yacc.getInfo());
		yacc.deposit(100);
		yacc.withdraw(1000);
		yacc.withdraw(500);
		yacc.withdraw(1000);
		
		zacc = new Checking("zname",1456,20000);
		out.println("Info: "+ zacc.getInfo());
		zacc.deposit(100);
		zacc.withdraw(1000);
		
		int comp = compare(xacc,yacc);
		out.println("xacc vs yacc = "+comp);
		comp = compare(xacc,zacc);
		out.println("xacc vs zacc = "+comp);
		comp = compare(yacc,zacc);
		out.println("yacc vs zacc = "+comp);
	}
	
	static int compare(BankAccount a, BankAccount b)
	{
		// Polymorphism
		if (a.remain()>b.remain())
			return 1;
		else if (a.remain()<b.remain())
			return -1;
		else
			return 0;
	}
}
