library IEEE; 
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity FSM is
    port(clk, rst, ALU_eq: in std_logic;
         op: in std_logic_vector(2 downto 0);
         PC_en, Mem_mux, Mem_en, Mem_rw, IR_en, Dest_mux, RData_mux, Reg_en,
         ALU_mux1, ALU_op: out std_logic;
         ALU_mux2: out std_logic_vector(1 downto 0));
end FSM;

architecture bhv of FSM is	
    type STATE_TYPE is (FET_0, DEC_1, ADD_2, ADD_3, NAND_4, NAND_5, LW_6, LW_7, LW_8, SW_9, SW_10, BEQ_11, BEQ_12, JALR_13, JALR_14, JALR_15, HALT_16);
    signal cpu_state: STATE_TYPE;

    constant ADD: std_logic_vector(2 downto 0) := "000";
    constant NAD: std_logic_vector(2 downto 0) := "001";
    constant LW: std_logic_vector(2 downto 0) := "010";
    constant SW: std_logic_vector(2 downto 0) := "011";
    constant BEQ: std_logic_vector(2 downto 0) := "100";
    constant JALR: std_logic_vector(2 downto 0) := "101";
    constant HALT: std_logic_vector(2 downto 0) := "110";
    constant NOOP: std_logic_vector(2 downto 0) := "111";

begin	  
    state_machine: process (rst, clk)
    begin
        if (rst = '1') then
            PC_en <= '0';
            Mem_mux <= '0';	
            Mem_en <= '0';
            Mem_rw <= '0';
            IR_en <= '0';
            Dest_mux <= '0';
            RData_mux <= '0';
            Reg_en <= '0';
            ALU_mux1 <= '0';
            ALU_mux2 <= "10";
            ALU_op <= '0';
            cpu_state <= FET_0;
        elsif (clk'event and clk = '1') then
            case cpu_state is
                when FET_0 =>
                    PC_en <= '0';
                    Mem_mux <= '0';
                    Mem_en <= '1';
                    Mem_rw <= '0';
                    IR_en <= '1';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= '0';
                    ALU_mux2 <= "01";
                    ALU_op <= '0';
                    cpu_state <= DEC_1;

                when DEC_1 =>
                    PC_en <= '1';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= 'X';
                    ALU_mux2 <= "XX";
                    ALU_op <= 'X';

                    case op is
                        when ADD =>
                            cpu_state <= ADD_2;
                        when NAD =>
                            cpu_state <= NAND_4;
                        when LW =>
                            cpu_state <= LW_6;
                        when SW =>
                            cpu_state <= SW_9;
                        when BEQ =>
                            cpu_state <= BEQ_11;
                        when JALR =>
                            cpu_state <= JALR_13;
                        when HALT =>
                            cpu_state <= HALT_16;
                        when others =>
                            cpu_state <= FET_0;
                    end case;

                when ADD_2 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= '1';
                    ALU_mux2 <= "00";
                    ALU_op <= '0';
                    cpu_state <= ADD_3;
                when ADD_3 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= '1';
                    RData_mux <= '1';
                    Reg_en <= '1';
                    ALU_mux1 <= 'X';
                    ALU_mux2 <= "XX";
                    ALU_op <= 'X';
                    cpu_state <= FET_0;

                when NAND_4 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= '1';
                    ALU_mux2 <= "00";
                    ALU_op <= '1';
                    cpu_state <= NAND_5;
                when NAND_5 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= '1';
                    RData_mux <= '1';
                    Reg_en <= '1';
                    ALU_mux1 <= 'X';
                    ALU_mux2 <= "XX";
                    ALU_op <= 'X';
                    cpu_state <= FET_0;

                when LW_6 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= '1';
                    ALU_mux2 <= "11";
                    ALU_op <= '0';
                    cpu_state <= LW_7;
                when LW_7 =>
                    PC_en <= '0';
                    Mem_mux <= '1';
                    Mem_en <= '1';
                    Mem_rw <= '0';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= 'X';
                    ALU_mux2 <= "XX";
                    ALU_op <= 'X';
                    cpu_state <= LW_8;
                when LW_8 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= '0';
                    RData_mux <= '0';
                    Reg_en <= '1';
                    ALU_mux1 <= 'X';
                    ALU_mux2 <= "XX";
                    ALU_op <= 'X';
                    cpu_state <= FET_0;

                when SW_9 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= '1';
                    ALU_mux2 <= "11";
                    ALU_op <= '0';
                    cpu_state <= SW_10;
                when SW_10 =>
                    PC_en <= '0';
                    Mem_mux <= '1';
                    Mem_en <= '1';
                    Mem_rw <= '1';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= 'X';
                    ALU_mux2 <= "XX";
                    ALU_op <= 'X';
                    cpu_state <= FET_0;

                when BEQ_11 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= '0';
                    ALU_mux2 <= "11";
                    ALU_op <= '0';
                    cpu_state <= BEQ_12;
                when BEQ_12 =>
                    PC_en <= ALU_eq;
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= '1';
                    ALU_mux2 <= "00";
                    ALU_op <= 'X';
                    cpu_state <= FET_0;

                when JALR_13 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= '0';
                    ALU_mux2 <= "10";
                    ALU_op <= '0';
                    cpu_state <= JALR_14;
                when JALR_14 =>
                    PC_en <= '0';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= '0';
                    RData_mux <= '1';
                    Reg_en <= '1';
                    ALU_mux1 <= '1';
                    ALU_mux2 <= "10";
                    ALU_op <= '0';
                    cpu_state <= JALR_15;
                when JALR_15 =>
                    PC_en <= '1';
                    Mem_mux <= 'X';
                    Mem_en <= '0';
                    Mem_rw <= 'X';
                    IR_en <= '0';
                    Dest_mux <= 'X';
                    RData_mux <= 'X';
                    Reg_en <= '0';
                    ALU_mux1 <= 'X';
                    ALU_mux2 <= "XX";
                    ALU_op <= 'X';
                    cpu_state <= FET_0;

                when HALT_16 =>
                    PC_en <= '0';
                    Mem_mux <= '0';
                    Mem_en <= '0';
                    Mem_rw <= '0';
                    IR_en <= '0';
                    Dest_mux <= '0';
                    RData_mux <= '0';
                    Reg_en <= '0';
                    ALU_mux1 <= '0';
                    ALU_mux2 <= "00";
                    ALU_op <= '0';
                    cpu_state <= HALT_16;

                when others =>
                    cpu_state <= FET_0;
            end case;
        end if;
    end process state_machine;
end bhv;
