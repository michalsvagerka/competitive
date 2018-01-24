#include "../l/lib.h"
// #include "../l/mod.h"
#include <numeric>


struct image {
	int width;
	int height;
	int offsetX;
	int offsetY;

	vector<vector<int> > data;

    int black() {
        int s = 0;
        for (auto &d:data) for (auto &dd:d) s += dd;
        return s;
    }

	void cut_left(int amount) {
		offsetX += amount;
		width -= amount;
		for (int y = 0; y < height; ++y) {
			vector<int> & v = data[y];
			v.erase(v.begin(),v.begin() + amount);
		}
	}

	void cut_right(int amount) {
		width -= amount;
		for (int y = 0; y < height; ++y) {
			vector<int> & v = data[y];
			v.erase(v.end() - amount, v.end());
		}
	}

	void cut_top(int amount) {
		offsetY += amount;
		height -= amount;
		data.erase(data.begin(),data.begin() + amount);
	}

	void cut_bottom(int amount) {
		height -= amount;
		data.erase(data.end() - amount,data.end());
	}

    void average(int w) {
        vector<vector<int>> newData(height - 2*w, vector<int>(width - 2*w));
        height -= 2*w;
        width -= 2*w;
        offsetX += w;
        offsetY += w;
        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                int s = 0;
                for (int a = 0; a <= 2*w ; ++a) {
                    for (int b = 0; b <= 2*w; ++b) {
                        s += data[r+a][c+b];
                    }
                }
                newData[r][c] = s > 2*w*(w+1);
            }
        }
        swap(data,newData);
    }
};

void read_pgm(istream & stream, image & image_out) {
	string line;
	getline(stream, line); // P2
	getline(stream, line); // name

	image_out.offsetX = 0;
	image_out.offsetY = 0;

	int gray;
	stream >> image_out.width >> image_out.height >> gray;

	image_out.data.resize(image_out.height);
	for (int y = 0; y < image_out.height; ++y) {
		image_out.data[y].resize(image_out.width);
		for (int x = 0; x < image_out.width; ++x) {
			int z;
			stream >> z;
			image_out.data[y][x] = 1 - z;
		}
	}
}

void sum_row_cols(const image & image, vector<int> & rows_out, vector<int> & cols_out) {

	rows_out.resize(image.height);
	fill(rows_out.begin(), rows_out.end(), 0);

	cols_out.resize(image.width);
	fill(cols_out.begin(), cols_out.end(), 0);

	for (int y = 0; y < image.height; ++y) {
		const vector<int> & row = image.data[y];
		for (int x = 0; x < image.width; ++x) {
			rows_out[y] += row[x];
			cols_out[x] += row[x];
		}
	}
}

int average(vector<int> & v) {
	return accumulate(v.begin(), v.end(), 0) / v.size();
}

int median_gt(vector<int> & v, int threshold) {
	int sum = 0;
	int count = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] >= threshold) {
//			cout << i << " ";
			sum += i;
			++count;
		}
	}

	int m = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] >= threshold) {
			m += 2;
			if (m >= count) {
				// cout << i << endl;
				return i;
//				break;
			}
		}
	}

	cout << (sum / count) << endl;
	return sum / count;
}



#define MINBOUND 200
#define CUT_SIZE 100

class gorilavhmle {
public:
    void solve(istream& cin, ostream& cout) {
        image img;
        read_pgm(cin, img);

        img.average(5);
        img.average(5);

        int x;
        int y;
        for (int i = 0; i < 6; ++i) {
            vector<int> rows, cols;
            sum_row_cols(img, rows, cols);
            x = median_gt(cols, average(cols));
            y = median_gt(rows, average(rows));

//		cout << img.offsetX + x << " " << img.offsetY + y << endl;
            img.cut_left(min(CUT_SIZE, max(x - MINBOUND, 0)));
            img.cut_right(min(CUT_SIZE, max(img.width - x - MINBOUND, 0)));
            img.cut_top(min(CUT_SIZE, max(y - MINBOUND, 0)));
            img.cut_bottom(min(CUT_SIZE, max(img.height - y - MINBOUND, 0)));
//		cout << img.width << " " << img.height << endl;
        }


        vector<int> rows, cols;
        sum_row_cols(img, rows, cols);
        x = median_gt(cols, average(cols));
        y = median_gt(rows, average(rows));


        int black = img.black();
        cout << img.offsetX + x << " " << img.offsetY + y << endl;
    }
};
