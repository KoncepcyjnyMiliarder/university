#include <iostream>
#include <string>
#include <router.hpp>
#include <ip_helpers.hpp>

int main()
{
  try
  {
    unsigned netcount;
    std::cin >> netcount;
    router rrrawr;

    while (netcount-- != 0)
    {
      std::string ip, dummy;
      unsigned distance;
      std::cin >> ip >> dummy >> distance;
      rrrawr.add_local_network(ip, distance);
    }

    while (1)
    {
      rrrawr.print();
      rrrawr.listen(5);
      rrrawr.broadcast();
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }
  return 0;
}
