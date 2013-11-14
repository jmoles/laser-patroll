#include "ImprovedBiotonic.hpp"

ImprovedBiotonic::ImprovedBiotonic() {

}

ImprovedBiotonic::~ImprovedBiotonic() {

}

void ImprovedBiotonic::Sort(DataType &data_in) {
	std::sort(data_in.begin(), data_in.end());
}
