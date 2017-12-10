import static java.lang.System.*;
import java.util.*;

public class MovieDB
{
	
	private static Scanner input = new Scanner(in);
	
	public static void main(String[] args)
	{
		Movie[] Movies = new Movie[100];
		int i=0;
		out.println("Welcome to the Movie DataBase!");
		
		
		while(true) {
			out.println("1: Add a new movie\n2: Show Movie Database\n3: Add a review\n4: Show Reviews\n0: Exit");
			int c = input.nextInt();
			input.nextLine();
			
			if (c==1)
			{
				out.print("Movie title: ");
				String mname = input.nextLine();

				out.print("Year: ");
				String myear = input.nextLine();

				out.print("Production: ");
				String mprod = input.nextLine();

				out.print("Director: ");
				String mdir = input.nextLine();
				Movies[i++] = new Movie(mname,myear,mprod,mdir);
			}
			else if (c==2)
			{
				for (int k=0;k<i;k++)
					out.println("Movie #"+k+"\n"+Movies[k].getMovieInfo()+"\n");
			}
			else if (c==3)
			{
				out.print("Enter movie's number to add review: ");
				int m=input.nextInt();
				input.nextLine();
				if (m>=i)
					out.println("There is not such a movie in the database");
				else
				{
					out.print("Enter date: ");
					String date = input.nextLine();
					out.print("Enter rate(1-5): ");
					int rate = input.nextInt();
					input.nextLine();
					out.print("Enter username: ");
					String username = input.nextLine();
					out.print("Enter review: ");
					String review = input.nextLine();
					Movies[m].insertReview(date, rate, username, review);
				}
			}
			else if (c==4)
			{
				out.print("Enter movie's number to show reviews: ");
				int m=input.nextInt();
				input.nextLine();
				if (m>=i)
					out.println("There is not such a movie in the database");
				else
				{
					out.println("Max rate for this movie is: "+Movies[m].maxReview());
					out.println(Movies[m].showReviews());
					
					
				}
			}
			else if (c==0)
			{
				break;
			}
		}
		
		
			
	}
}

class Movie 
{
	private String name;
	private String year;
	private String production;
	private String director;
	private String movieinfo;
	private Review[] Review = new Review[100];
	private int i;
	
	//constructors
	public Movie(String n, String y, String p, String d)
	{
		name=n;
		year=y;
		production=p;
		director=d;
		i=0;
	}
	
	public Movie()
	{
		name="";
		year="";
		production="";
		director="";
		i=0;
	}
	//methods
	public String getName()
	{
		return name;
	}
	
	public String getYear()
	{
		return year;
	}
	
	public String getProduction()
	{
		return production;
	}
	
	public String getDirector()
	{
		return director;
	}
	
	public String getMovieInfo()
	{
		movieinfo = "Movie: "+name+"\n"+"Year: "+year+"\n"+"Production: "+production+"\n"+"Director: "+director;
		return movieinfo;
	}
	
	public void insertReview(String d, int rt, String u, String r)
	{
		Review[i++]=new Review(d,rt,u,r);
	}
	
	public String showReviews()
	{
		String revret="";
		for(int k=0;k<i;k++)
		{
			revret = revret+Review[k].getReview()+"\n";
		}
		revret = "Reviews for movie "+name+":\n"+revret;
		return revret;
	}
	
	public int maxReview()
	{
		int max=0;
		for(int k=0;k<i;k++)
			if (Review[k].getRate()>max)
				max=Review[k].getRate();
		return max;
			
	}
}


class Review extends Movie{
	
	private String date;
	private int rate;
	private String username;
	private String rev;
	private String review;

	public Review(String d, int rt, String u, String r)
	{
		date=d;
		rate=rt;
		username=u;
		rev=r;
	}
	
	public String getReview()
	{
		review="["+date+"]"+"(rate:"+rate+"/5) "+username+": "+"\""+rev+"\"";
		return review;
	}
	
	public int getRate()
	{
		return rate;
	}
}

