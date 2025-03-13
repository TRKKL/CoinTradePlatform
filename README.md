# CoinTradePlatform


Merkel Market Simulator is a simple cryptocurrency market simulator that allows users to place bids and asks, track market statistics, and manage their wallet. The data is processed from a CSV file containing historical market data.

## Features
- View available trading products
- Place buy (bid) and sell (ask) orders
- View market statistics (highest, lowest, and average ask prices)
- Check wallet balance
- Move forward in time to simulate market changes

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/your-username/merkel-market-simulator.git
   ```
2. Navigate to the project directory:
   ```sh
   cd merkel-market-simulator
   ```
3. Compile the program:
   ```sh
   g++ -o MerkelMain MerkelMain.cpp OrderBook.cpp CSVReader.cpp Wallet.cpp -std=c++11
   ```
4. Run the program:
   ```sh
   ./MerkelMain
   ```

## Usage
Once the program is running, a menu will be displayed with the following options:

1. **Print Help** – Displays usage instructions.
2. **Print Market Statistics** – Shows available products, the number of asks, highest ask price, and lowest ask price.
3. **Place an Ask Order** – Allows the user to submit a sell order by specifying the product, price, and amount.
4. **Place a Bid Order** – Allows the user to submit a buy order.
5. **Print Wallet** – Displays the current balance of currencies.
6. **Average Price** – Calculates and displays the average ask price for each product.
7. **Next Timeframe** – Moves to the next available time frame in the dataset.

## File Structure
- `MerkelMain.cpp/.h` – Main entry point of the application, handling user input and menu interaction.
- `OrderBook.cpp/.h` – Manages market orders, matching bids to asks.
- `OrderBookEntry.h` – Represents a single order in the market.
- `CSVReader.cpp/.h` – Reads market data from CSV files.
- `Wallet.cpp/.h` – Manages user funds and processes transactions.

## Requirements
- C++11 or later
- A compiler supporting C++11 (e.g., g++, clang++)

## License
This project is open-source and available under the MIT License.

## Author
- [@MehmetEminTurkkal](https://github.com/TRKKL)

