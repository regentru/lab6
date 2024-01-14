#include <iostream>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

class NetAddress {
private:
	uint32_t address{ 0 };
    uint32_t netmask{ 0 };
    string straddress{}, strnetmask{};
    
	vector<uint8_t> split(string s, char delim) {
        vector<uint8_t> result;
        size_t pos = 0;
        while ((pos = s.find(delim)) != std::string::npos) {
            result.push_back(stoi(s.substr(0, pos)));
            s.erase(0, pos + 1);
        }
        result.push_back(stoi(s));
        return result;
    }

public:

    NetAddress(string ip, string mask) {

        auto ips = split(ip, '.');
        for (int i = 0; i < 4; ++i) {
            address |= (ips[i] << (i * 8));
        }

        auto masks = split(mask, '.');
        for (int i = 0; i < 4; ++i) {
            netmask |= (masks[i] << (i * 8));
        }
    }

    void getNetworkAddress() const {
        uint32_t networkAddr = address & netmask;

        // ff - 8 bit limitation
        cout << (networkAddr & 0xFF) << "."
            << (networkAddr >> 8 & 0xFF) << "."
            << (networkAddr >> 16 & 0xFF) << "."
            << (networkAddr >> 24);

    }

    NetAddress(uint32_t address, uint32_t netmask)
        : address(address), netmask(netmask) {}

    NetAddress operator&(const NetAddress& other) const {
        return NetAddress(address & other.address, netmask & other.netmask);
    }

    bool operator==(const NetAddress& other) const {
        return address == other.address && netmask == other.netmask;
    }

    friend std::ostream& operator<<(std::ostream& os, const NetAddress& na);

    friend std::istream& operator>>(std::istream& os, NetAddress& na);
};

std::ostream& operator<<(std::ostream& os, const NetAddress& na) {
    os << std::bitset<8>(na.address >> 24) << "."
        << std::bitset<8>(na.address >> 16) << "."
        << std::bitset<8>(na.address >> 8) << "."
        << std::bitset<8>(na.address) << "/"
        << std::bitset<32>(na.netmask);
    return os;
}

std::istream& operator>>(std::istream& os, NetAddress& na) {
    os >> na.straddress >> na.strnetmask;
    na = NetAddress(na.straddress, na.strnetmask);
    return os;
}


int main(int argc, char** argv) {
	NetAddress ip("192.168.0.1", "255.255.255.0");
    NetAddress subnet = ip & ip;

    std::cout << "IP: " << ip << std::endl;
    std::cout << "Subnet: ";
    ip.getNetworkAddress();
    std::cout << std::endl;

    std::cout << "('192.168.0.1', '255.255.255.0') == ('192.168.0.1', '255.255.255.0') ? -> " << (ip == ip) << std::endl;

    std::cout << "Enter ip and mask: ";
    std::cin >> ip;
    std::cout << "You write: " << ip << std::endl;
	
	return 0;
}
