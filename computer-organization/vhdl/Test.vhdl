library IEEE;
use IEEE.std_logic_1164.all;

entity test is
    port(PC, IR: out STD_LOGIC_VECTOR (31 downto 0));
end test;

architecture bhv of test is

    component LC2K
        port(clk, rst: in std_logic;
             outPC, outMem, outIR, outRF1, outRF2, inALU1, inALU2, outALU, outp: out std_logic_vector(31 downto 0));
    end component;

    constant period: time := 100 ps;

    signal rst: STD_LOGIC;
    signal clk: STD_LOGIC;
    signal outMem: std_logic_vector(31 downto 0);
    signal outRF1: std_logic_vector(31 downto 0);
    signal outRF2: std_logic_vector(31 downto 0);
    signal inALU1: std_logic_vector(31 downto 0);
    signal inALU2: std_logic_vector(31 downto 0);
    signal outALU: std_logic_vector(31 downto 0);
    signal outp: std_logic_vector(31 downto 0);

begin
    RSTprocess: process
    begin
        rst <= '1';
        wait for period * 2;
        rst <= '0';
        wait;
    end process RSTprocess;

    CLKprocess: process
    begin
        clk <= '0';
        wait for period;
        clk <= '1';
        wait for period;
    end process CLKprocess;

    U_CPU: LC2K port map (clk, rst, PC, outMem, IR, outRF1, outRF2, inALU1, inALU2, outALU, outp);

end bhv;
