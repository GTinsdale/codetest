/*
 * Blazing Griffin code test
 * Part 3 : Game logic
 *
 * Trevor Fountain
 * April 2013
 */

#include <vector>
#include <map>
#include <iostream>

/**
   @brief Represents a point in space.
*/
class Star
{
public:
  /// The x-coordinate of this Star's location, in pixel coordinates
  double x;
  /// The y-coordinate of this Star's location, in pixel coordinates
  double y;

  /// Create a star at the specified location in pixel coordinates
  Star(double x, double y) { this->x = x; this->y = y; }

  /// Print this Star as a coordinate pair
  friend std::ostream& operator<<( std::ostream &out, const Star &star );
};

std::ostream &operator<<(std::ostream &out, const Star &star)
{
  out << "(" << star.x << ", " << star.y << ")";

  return out;
}

/// A randomly-accessible list of Stars
typedef std::vector<Star *> StarList;
/// Maps Stars onto lists of adjacent Stars
typedef std::map<Star *, StarList> StarAdjacencyList;

/**
   @brief Hold information about stars and lanes.
*/
class Galaxy
{
protected:
  /// A list of Stars in the Galaxy
  StarList stars;
  /// A map of lanes between Stars
  StarAdjacencyList lanes;

public:
  /// Create the default Galaxy
  Galaxy();

  // Get a star
  Star *getStar(int index);

  // Return a list of stars to traverse in order to move from A to B.
  StarList getRouteBetween(Star *a, Star *b, StarList current_route, int current_best);
};

Galaxy::Galaxy()
{
  // Set up a simple galaxy
  // ...with a few stars
  stars.push_back(new Star(0, 0));
  stars.push_back(new Star(50, 30));
  stars.push_back(new Star(100, 0));
  stars.push_back(new Star(40, -10));
  stars.push_back(new Star(60, -10));

  // ...and a few lanes between them
  lanes[stars[0]].push_back(stars[1]);
  lanes[stars[0]].push_back(stars[3]);
  lanes[stars[1]].push_back(stars[0]);
  lanes[stars[1]].push_back(stars[4]);
  lanes[stars[1]].push_back(stars[2]);
  lanes[stars[2]].push_back(stars[1]);
  lanes[stars[2]].push_back(stars[4]);
  lanes[stars[3]].push_back(stars[0]);
  lanes[stars[3]].push_back(stars[4]);
  lanes[stars[4]].push_back(stars[1]);
  lanes[stars[4]].push_back(stars[2]);
  lanes[stars[4]].push_back(stars[3]);
}

Star *Galaxy::getStar(int index)
{
  if (index < 0 || index >= stars.size())
    {
      return NULL;
    }

  return stars[index];
}

void printStarList(StarList list)
{
  for(int i=0; i<list.size(); i++)
    {
      Star node=*list[i];

      std::cout << "star " << i << " : (" << node.x << ", " << node.y << ")\n";
    }
}

//------------------------------------------------------------------------------

StarList Galaxy::getRouteBetween(Star *a, Star *b, StarList current_route, int current_best)
{//getRouteBetween(...) starts

  //printf("entering getRouteBetween(...)\n");
  Star starA=*a;
  Star starB=*b;

  //  printStarList(current_route);
  StarList route;
  
  //add the current star to the route
  current_route.push_back(a);
  
  //create list of possible stars
  std::vector<Star *> nodes = lanes[a];
  
  //check the nodes list for stars we have already visited
  //this is not a particularly nice way of doing this.
  for(int exists=0;exists<current_route.size();exists++)
    {
      Star aStar = *current_route[exists];
      for (int exists_inner=0; exists_inner<nodes.size(); exists_inner++)
	{
	  Star bStar=*nodes[exists_inner];
	  if((aStar.x==bStar.x)&&(aStar.y==bStar.y))
	    {
	      //if the star exists erase it
	      nodes.erase(nodes.begin()+exists_inner);
	    }
      
	}
    }
  
  //for each of the nodes
  for(int i=0;i<nodes.size();i++)
    {//for nodes.size() Starts
      Star node=*nodes[i];

      //see if the current node has any children already in the route
      //(avoid infinte loop - not an efficient method but hey...)
      for(int c=0;c<current_route.size();c++)
	{
	  Star route_star=*current_route[c];

	  if(!((node.x==route_star.x) && (node.y==route_star.y)))
	    {
	      //check to see if the node is our destination
	      //if it is return the route
	      if((node.x==starB.x) && (node.y==starB.y))
		{
		  //add the current node to the route
		  current_route.push_back(nodes[i]);
		  //return the route
		  return current_route;
		}
	      //Other wise shift to the new node and repeat
	      else
		{
		  //recursive call for the next node
		  StarList possible_route=getRouteBetween(nodes[i], b, current_route, current_best);
		  //if the route is greater than 0 or less than the current best route
		  //add it to the current route
		  if((current_best==0) || (possible_route.size()<current_best))
		    {
		      current_best=possible_route.size();
		      route.insert(route.end(), possible_route.begin(), possible_route.end());
		    }
		}
	    }//if node==route_star ends
	}//for current_route.size() ends
    }//for nodes.size() ends
  //once we have hit all the nodes in this recursion return our route for this node
  return route;
}//getRouteBetween(....) ends

//------------------------------------------------------------------------------

/// Helper function to print a route to the console
void printRoute(StarList route)
{
  std::cout << "[" << route.size() << "]:";

  // Don't print 0-length routes!
  if (route.size() <= 0)
    {
      std::cout << std::endl;
      return;
    }

  for(int starIndex = 0; starIndex < route.size()-1; ++starIndex)
    {
      std::cout << *route[starIndex] << " -> ";
    }

  if (route.size() > 0)
    {
      std::cout << *route[route.size()-1] << std::endl;
    }
}

int main(int argc, char **argv)
{
  Galaxy galaxy;
  StarList current_route;

  printRoute(galaxy.getRouteBetween(galaxy.getStar(0), galaxy.getStar(2), current_route, 0));
}
