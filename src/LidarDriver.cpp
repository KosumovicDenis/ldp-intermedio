#include "../include/LidarDriver.h"

LidarDriver::LidarDriver(int degree): index {-1}, oldest_element_idx {-1}, RESOLUTION {(POV/degree) + 1}
{
  if(!is_valid(degree)) throw InvalidDegree();
}

bool LidarDriver::is_valid(int degree) const
{
  return degree >= 0.1 && degree <= 1;
}

void LidarDriver::new_scan(const std::vector<double>& buff)
{
  index = ++index % BUFFER_DIM;
  if (scan.size() < BUFFER_DIM)
  {
    scan.push_back(std::vector<double>(RESOLUTION));
  }

  int min = buff.size() > scan[0].size() ? scan[0].size(): buff.size();
  for (size_t i = 0; i < min; i++) {
    scan[index].at(i) = buff.at(i);
  }
  for (size_t i = min; i < scan[0].size(); i++) {
    scan[index].at(i) = 0;
  }
  
  if(oldest_element_idx == index) oldest_element_idx= ++oldest_element_idx % BUFFER_DIM; // Da rivedere
  if(oldest_element_idx == -1 ) {
    oldest_element_idx = 0;
  }
}

std::vector<double> LidarDriver::get_scan()
{
  if(oldest_element_idx == -1) throw InvalidScan();

  int tmp = oldest_element_idx;
  if (oldest_element_idx == index) 
  {
    oldest_element_idx = -1;
    index = -1;
  }
  else 
  {
   oldest_element_idx= ++oldest_element_idx % BUFFER_DIM;
  }
  return scan.at(tmp);
}

void LidarDriver::clear_buffer()
{
  index = -1;
  oldest_element_idx = -1;
  for(int i = 0; i < scan.size(); i++)
    scan[i].clear();
}


std::ostream& operator<<(std::ostream& os, const LidarDriver& l) {
  if (l.oldest_element_idx == -1) return os;
  int distance = l.index < l.oldest_element_idx ? l.BUFFER_DIM + l.index - l.oldest_element_idx : l.index- l.oldest_element_idx;
  for (int i = 0; i <= distance; i++)
  {
    os << "Buffer n°" << i + 1 << ":\n";
    int k = (l.oldest_element_idx + i) % l.BUFFER_DIM;
    for (int j = 0; j < l.scan[k].size(); j++)
    {
      os << l.scan[k][j] << '\t';
    }
    os << '\n';
  }

  return os;
}