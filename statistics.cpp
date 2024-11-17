#include <iostream>
#include <limits>

#include <math.h>
#include <vector>
#include <numeric>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;

//	virtual double getVal() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:


	Max() : m_max{std::numeric_limits<double>::lowest()} {
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:

	void update(double next) override {
		n++;
		sum += next;
	}

	double eval() const override {
		return sum/n;
	}

	const char * name() const override {
		return "mean";
	}

private:
	int n=0;
	double sum ;
};


class Std : public Mean {
public:

	 void update(double next) override {
		 number.push_back(next);
	}

	 double eval() const override {
        double mean = std::accumulate(number.begin(), number.end(), 0.0) / number.size();
		
		double sum_Sq;
		for (size_t i = 0; i < number.size(); ++i) {
            sum_Sq += powl((number[i] - mean), 2);
        }
	 	return sqrt(sum_Sq/(number.size()-1));
	 }

	const char * name() const override {
		return "std";
	}

private:
	std::vector<double> number;
};

int main() {

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}