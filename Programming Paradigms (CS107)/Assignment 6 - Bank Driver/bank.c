#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <semaphore.h>

#include "error.h"

#include "bank.h"
#include "branch.h"
#include "account.h"
#include "report.h"

/*
 * allocate the bank structure and initialize the branches.
 */
Bank*
Bank_Init(int numBranches, int numAccounts, AccountAmount initalAmount,
          AccountAmount reportingAmount,
          int numWorkers)
{

  Bank *bank = malloc(sizeof(Bank));

  if (bank == NULL) {
    return bank;
  }
  bank->work_done = 0;
  sem_init(&bank->work_done_lock, 0, 1);
  sem_init(&bank->next_day_lock, 0, 0);
  sem_init(&bank->wait_lock, 0, 0);
  sem_init(&bank->transfer_lock, 0, 1);
  Branch_Init(bank, numBranches, numAccounts, initalAmount);
  Report_Init(bank, reportingAmount, numWorkers);

  return bank;
}

/*
 * get the balance of the entire bank by adding up all the balances in
 * each branch.
 */
int
Bank_Balance(Bank *bank, AccountAmount *balance)
{
  assert(bank->branches);

  for(unsigned int branch = 0; branch < bank->numberBranches; branch++)
    sem_wait(&bank->branches[branch].branch_lock);
  AccountAmount bankTotal = 0;
  for (unsigned int branch = 0; branch < bank->numberBranches; branch++) {
    
    AccountAmount branchBalance;
    int err = Branch_Balance(bank,bank->branches[branch].branchID, &branchBalance);
    if (err < 0) {
      for(unsigned int branchi = 0; branchi < bank->numberBranches; branchi++)
        sem_post(&bank->branches[branchi].branch_lock);
      return err;
    }
    bankTotal += branchBalance;

  }

  *balance = bankTotal;

  for(unsigned int branch = 0; branch < bank->numberBranches; branch++)
    sem_post(&bank->branches[branch].branch_lock);

  return 0;
}
/*
 * tranverse and validate each branch.
 */
int
Bank_Validate(Bank *bank)
{
  assert(bank->branches);
  int err = 0;

  for (unsigned int branch = 0; branch < bank->numberBranches; branch++) {
    int berr = Branch_Validate(bank,bank->branches[branch].branchID);
    if (berr < 0) {
      err = berr;
    }
  }
  return err;
}

/*
 * compare the data inside two banks and see they are exactly the same;
 * it is called in BankTest.
 */
int
Bank_Compare(Bank *bank1, Bank *bank2)
{
  int err = 0;
  if (bank1->numberBranches != bank2->numberBranches) {
    fprintf(stderr, "Bank num branches mismatch\n");
    return -1;
  }

  for (unsigned int branch = 0; branch < bank1->numberBranches; branch++) {
    int berr = Branch_Compare(&bank1->branches[branch],
                              &bank2->branches[branch]);
    if (berr < 0) {
      err = berr;
    }
  }

  int cerr = Report_Compare(bank1, bank2);
  if (cerr < 0)
    err = cerr;

  return err;

}
